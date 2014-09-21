#include <pd2mo.h>
#include <evalp.h>

/**
check if modelChild is Atomic
*/

using namespace std;

namespace pd2mo{

string getFullPath(){
        char szTmp[320];
        char pBuf[320];
        int len = 320;
        sprintf(szTmp, "/proc/%d/exe", getpid());
        int bytes = readlink(szTmp, pBuf, len);
        if(bytes >= 0)
                pBuf[bytes] = '\0';
        string ret(dirname(pBuf));
	return ret;
}

Pd2Mo::Pd2Mo(){
        classMap = new map<string, string>();
        sourceType = new map<string, string>();
        pd2mo_dir = getFullPath();
}

void Pd2Mo::transform(string filename, ostream * output, ostream * log){

        QString qfilename = QString::fromStdString(filename);
        
        (*log) << "Open File " << filename << endl;
        modelCoupled *model = parsePDS(qfilename);

        //Load class based on the coupledModel from file
        (*log) << "Load class list based on class map." << endl;
        AST_ClassList classList = getAsClassList(model, classMap, log); 
	list<tConnection> cList = getClassConnections(classList);
	
	setModelParameters(model, classList);

        //Rename each AST_Class variable based on name and position in the coupledmodel
        AST_ClassListIterator it;
	map <int, string> className = map <int, string>();
	int j = 0;
        foreach(it, classList){
		if(current_element(it)){
			PrefixMoVars pf = PrefixMoVars();
			stringstream sstm;
			sstm << current_element(it)->getAsDefinition()->name() << "_" << j << "_" ;
			pf.setPrefix(sstm.str());
                        current_element(it) = pf.visitClass(current_element(it));
			className[j] = sstm.str(); 
			(*log) << current_element(it) << "@" << j << endl;
                }else{  
			(*log) << "<<No Mapped Class>> @" << j << endl;
                }
		j++;
        }

        
        //Move all AST_Class List to a new "Model"
	AST_String name = new  string("Pd2Model");

	AST_ElementList elem = new list<AST_Element>();
	AST_CompositionElementList comp = new list<AST_CompositionElement>();

	AST_Composition composition = new AST_Composition_ (elem, comp);
	composition->setExternalFunctionCall(NULL);
	AST_Class modelMo = new AST_Class_Definition_(name, composition);
	modelMo->setPrefixes(CP_MODEL);


	AST_StatementList initStList = new list<AST_Statement>();
	AST_EquationList initEqList = new list<AST_Equation>();

	AST_CompositionEqsAlgs initialEqAlgsST = new AST_CompositionEqsAlgs_(initStList, true);
	AST_CompositionEqsAlgs initialEqAlgsEQ = new AST_CompositionEqsAlgs_(initEqList, true);

	comp->insert(comp->end(), new AST_CompositionElement_(initialEqAlgsST));
	comp->insert(comp->end(), new AST_CompositionElement_(initialEqAlgsEQ));

	AST_StatementList stList = new list<AST_Statement>();
	AST_EquationList eqList = new list<AST_Equation>();

	AST_CompositionEqsAlgs eqAlgsST = new AST_CompositionEqsAlgs_(stList);
	AST_CompositionEqsAlgs eqAlgsEQ = new AST_CompositionEqsAlgs_(eqList);

	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsST));
	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsEQ));

        foreach(it, classList){
		if(current_element(it)){
			Combine(elem, initStList, initEqList, stList, eqList, current_element(it));
			(*log) << current_element(it)->getAsDefinition()->name() << endl;
		}
	}


	//Add coupledmodel connections
        (*log) << "Add coupledmodel connections" << endl;;
	QList<modelConnection*> * lsIc = &(model->lsIC);
	QList<modelConnection*>::iterator itM;
	QList<modelChild * > * childs = &(model->childs);

	foreach(itM, lsIc){
		modelChild * srcModel = childs->at(current_element(itM)->childSource);
		modelChild * sinkModel = childs->at(current_element(itM)->childSink);

		AST_ExpressionList sinklt = new list<AST_Expression>();
		AST_ExpressionList sourcelt = new list<AST_Expression>();
		stringstream sincStream; 
		sincStream << className[current_element(itM)->childSink] << "u";
		stringstream sourceStream; 
		sourceStream<< className[current_element(itM)->childSource] << "y";
		if(className[current_element(itM)->childSource].empty() or
		className[current_element(itM)->childSink].empty()){
			continue;
		}

		string param = (*sourceType)[sinkModel->atomic->path.toStdString()];

		(*log) <<"param type:" << param << endl;
			sourcelt->insert(
				sourcelt->end(), 
				new AST_Expression_Integer_(
					current_element(itM)->sinkPort+1
					));
			sinklt->insert(
				sinklt->end(), 
				new AST_Expression_Integer_(
					current_element(itM)->sourcePort+1
					));

		AST_String source = new string(sincStream.str());
		AST_String sink = new string(sourceStream.str());
		AST_Expression_ComponentReference esource = 
		    new AST_Expression_ComponentReference_ ();
		AST_Expression_ComponentReference esink = 
		    new AST_Expression_ComponentReference_ ();
		esink->append(sink, sinklt);
		esource->append(source, sourcelt);
		AST_Equation_Equality eq = new AST_Equation_Equality_(esource, esink);
		eqList->insert(eqList->end(), eq);
		(*log) << eq << endl;

        }

	(*output) << modelMo;

}
void find_and_replace(string& source, string const& find, string const& replace)
{
    for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length() - find.length() + 1;
    }
}

string Pd2Mo::makeMoFileName(string pdfile){
    string mofile(pdfile);
    find_and_replace(mofile, "\\", "/");
    find_and_replace(mofile, ".h", ".mo");
    mofile = string(pd2mo_dir) + mofile;
    return mofile;
}

int fileExist(const char* filename)
{
  FILE* fptr = fopen(filename, "r");
  if (fptr != NULL)
  {
    fclose(fptr);
    return 1;
  }
  return 0;
}
/**

*/
AST_ClassList Pd2Mo::getAsClassList(modelCoupled * c, map<string, string> * m, ostream * log){
        (*log) << __PRETTY_FUNCTION__ << endl  ;
        QList< modelChild * >::iterator childsIterator;
        AST_ClassList st = new list<AST_Class>();
        int r;
	int modelId = 0;
        for (childsIterator = c->childs.begin(); 
                childsIterator != c->childs.end(); 
                ++childsIterator){
                modelChild * modelC = *childsIterator;

		string pdfile = modelC->atomic->path.toStdString();
		string mofile = makeMoFileName(pdfile);
		(*log) << "PowerDevs File " << pdfile << " to " << mofile << " " ;
		const char * c = mofile.c_str();
                if(fileExist(c)){
                        AST_StoredDefinition sd = parseFile(mofile, &r);
			(*log) << "FILE EXISTS "  <<  endl;
                        st->insert(st->end(), *(sd->models()->begin()));
                }else{
			(*log) << "FILE NO EXISTS" << endl;
                        st->insert(st->end(), NULL);
                }
		modelId++;
        }
        return st;
}

	void Pd2Mo::Combine(AST_ElementList elem,
				AST_StatementList initialStList, 
				AST_EquationList initialEqList,
				AST_StatementList stList, 
				AST_EquationList eqList,

				AST_Class a){

	AST_CompositionElementListIterator it;
	foreach(it, a->getAsDefinition()->composition()->compositionList()){
		if(current_element(it)->getEquationsAlgs()){
			if(current_element(it)->getEquationsAlgs()->isInitial()){
				initialStList->insert(initialStList->end(),
					current_element(it)->getEquationsAlgs()->getAlgorithms()->begin(),
					current_element(it)->getEquationsAlgs()->getAlgorithms()->end());
				initialEqList->insert(initialEqList->end(),
					current_element(it)->getEquationsAlgs()->getEquations()->begin(),
					current_element(it)->getEquationsAlgs()->getEquations()->end());
			}else{
				stList->insert(stList->end(),
					current_element(it)->getEquationsAlgs()->getAlgorithms()->begin(),
					current_element(it)->getEquationsAlgs()->getAlgorithms()->end());
				eqList->insert(eqList->end(),
					current_element(it)->getEquationsAlgs()->getEquations()->begin(),
					current_element(it)->getEquationsAlgs()->getEquations()->end());

			}

		}else if (current_element(it)->getElementList()->size() > 0){
			elem->insert(elem->end(), 
				current_element(it)->getElementList()->begin(),
				current_element(it)->getElementList()->end());
		}
	}
	
	elem->insert(elem->end(), 
		a->getAsDefinition()->composition()->elementList()->begin(), 
		a->getAsDefinition()->composition()->elementList()->end());
}

void Pd2Mo::setModelParameters(modelCoupled * model,
				AST_ClassList classList){
	AST_ClassListIterator cit;
	int k = 0;
	foreach(cit, classList){
		SetParameters ps = SetParameters();
		ps.setParameterName("p");
		modelAtomic * atomic = model->childs.at(k)->atomic;
		ps.setParametersList(atomic->paramsString.split(","));

		evalp ep = evalp();
		ep.setParams(atomic->paramsString.split(","));

		if(current_element(cit) != NULL){
			current_element(cit) = ps.visitClass(current_element(cit));
			current_element(cit) = ep.visitClass(current_element(cit));
		}
		k++;
	}
}

void Pd2Mo::setPath(string s){
	pd2mo_dir = s;
}


list<tConnection> Pd2Mo::getClassConnections(AST_ClassList classlist){
	list<tConnection> cList = list<tConnection>();

	for(AST_ClassListIterator mIter = classlist->begin(); mIter != classlist->end(); ++mIter){
		AST_Class c = (*mIter);
		if(NULL == c){
			continue;
		}

                AST_Class_Definition cd = c->getAsDefinition();
                AST_Class_Modification cm = c->getAsModification();
		cout << (long) cd << " " << (long)cm <<endl;
		if(cd){
			cout << "-----DEFINITION-----------\n";
			cout << c << endl;
		}else{
			cout << "--NO-DEFINITION-----------\n";
			//cout << c << endl;
		}
		//if(!cd) continue;
		//AST_CompositionElementList cl = c->getAsDefinition()->composition()->compositionList();
		//AST_Composition com = c->getAsDefinition()->composition();
		//AST_ArgumentList al = com->arguments();

		//for(AST_ArgumentListIterator it = al->begin(); it != al->end(); it++){
		//	AST_Argument_Modification mo = current_element(it)->getAsModification();
		//	cout << mo->name() << ":" << endl; 
		//	AST_Modification mods =mo->modification();
		//	if (MODCLASS == mods->modificationType()){
		//		AST_Modification_Class mc = mods->getAsClass();
		//		AST_ArgumentList al2 = mc->arguments();
		//		for(AST_ArgumentListIterator it2 = al2->begin(); it2 != al2->end(); it2++){
		//			AST_Argument ar = current_element(it2) ;
		//			cout << ar->getAsModification()->name() << " --> " ;
		//			AST_Modification_Equal me = ar->getAsModification()->modification()->getAsEqual();
		//			cout << me->exp() << endl;
		//		}
		//	}
		//}
	}
	return cList;
}


}
