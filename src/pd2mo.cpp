#include <pd2mo.h>

/**
check if modelChild is Atomic
*/

using namespace std;

namespace pd2mo{
Pd2Mo::Pd2Mo(){ 
        classMap = new map<string, string>();
        sourceType = new map<string, string>();
        pd2mo_dir = getFullPath();
}

char * Pd2Mo::getFullPath(){
        char szTmp[320];
        char pBuf[320];
        int len = 320;
        sprintf(szTmp, "/proc/%d/exe", getpid());
        int bytes = readlink(szTmp, pBuf, len);
        if(bytes >= 0)
                pBuf[bytes] = '\0';
        return dirname(pBuf);
}

void Pd2Mo::loadConfigFile(string file, ostream * log){
        //Class Mapping
        INIReader reader(file);
        if (reader.ParseError() < 0) {
            (* log )<< "Can't load '"<< file <<"'\n";
        }else{
                map<string, list <string> >::iterator it;
                map<string, list <string> > * keys = reader.getKeys();
                foreach(it, keys){
                        (*classMap)[(it->first)] = reader.Get(it->first, "Path", "n");
                        (*sourceType)[(it->first)] = reader.Get(it->first, "SourceType", "Unique");
                }
        }
        //Model Parameters
}

void Pd2Mo::transform(string filename, ostream * output, ostream * log){

        QString qfilename = QString::fromStdString(filename);
        
        (*log) << "Open File " << filename << endl;
        modelCoupled *model = parsePDS(qfilename);

        //Load class based on the coupledModel from file
        (*log) << "Load class list based on class map." << endl;
        AST_ClassList classList = getAsClassList(model, classMap, log); 

        //Rename each AST_Class variable based on name and position in the coupledmodel
        AST_ClassListIterator it;
	map <int, string> className = map <int, string>();
	int j = 0;
        foreach(it, classList){
		if(current_element(it)){
			PrefixMoVars pf = PrefixMoVars();
			stringstream sstm;
			sstm << current_element(it)->name() << "_" << j << "_" ;
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
	AST_Class modelMo = new AST_Class_(name, composition);
	modelMo->setPrefixes(CP_MODEL);

	AST_StatementList stList = new list<AST_Statement>();
	AST_EquationList eqList = new list<AST_Equation>();

	AST_CompositionEqsAlgs eqAlgsST = new AST_CompositionEqsAlgs_(stList);
	AST_CompositionEqsAlgs eqAlgsEQ = new AST_CompositionEqsAlgs_(eqList);

	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsST));
	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsEQ));

        foreach(it, classList){
		if(current_element(it)){
			Combine(elem, stList, eqList, current_element(it));
			cout << current_element(it)->name() << endl;
		}
	}


	//Add coupledmodel connections
        (*log) << "Add coupledmodel connections";
	QList<modelConnection*> * lsIc = &(model->lsIC);
	QList<modelConnection*>::iterator itM;
	QList<modelChild * > * childs = &(model->childs);

	foreach(itM, lsIc){
		modelChild * srcModel = childs->at(current_element(itM)->childSource);
		modelChild * sinkModel = childs->at(current_element(itM)->childSink);
		// cout << srcModel->atomic->path.toStdString()
		// 	<< "(" << current_element(itM)->sourcePort << ")-->"
		// 	<< sinkModel->atomic->path.toStdString() 
		// 	<< "(" << current_element(itM)->sinkPort << ")" << endl;

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

		cout <<"param type:" << param << endl;
		if(param.compare("Array") == 0){
			sourcelt->insert(
				sourcelt->end(), 
				new AST_Expression_Integer_(
					current_element(itM)->sinkPort
					));
		}

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
		cout << eq << endl;

        }

	cout << modelMo<< endl;

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
                if(m->count(modelC->atomic->path.toStdString())>0){
                        string pdfile = modelC->atomic->path.toStdString();
                        string mofile = (*m)[pdfile];
                        (*log) << "PowerDevs File " << pdfile << " to " << mofile << endl;
                        AST_StoredDefinition sd = parseFile(mofile, &r);
                        st->insert(st->end(), *(sd->models()->begin()));
                }else{
                        st->insert(st->end(), NULL);
                }
		modelId++;
        }
        return st;
}

	void Pd2Mo::Combine(AST_ElementList elem,
				AST_StatementList stList, 
				AST_EquationList eqList,
				AST_Class a){



	AST_CompositionElementListIterator it;
	foreach(it, a->composition()->compositionList()){
		if(current_element(it)->getEquationsAlgs()){
			stList->insert(stList->end(),
				current_element(it)->getEquationsAlgs()->getAlgorithms()->begin(),
				current_element(it)->getEquationsAlgs()->getAlgorithms()->end());
			eqList->insert(eqList->end(),
				current_element(it)->getEquationsAlgs()->getEquations()->begin(),
				current_element(it)->getEquationsAlgs()->getEquations()->end());

		}else if (current_element(it)->getElementList()->size() > 0){
			elem->insert(elem->end(), 
				current_element(it)->getElementList()->begin(),
				current_element(it)->getElementList()->end());
		}
	}
	
	elem->insert(elem->end(), 
		a->composition()->elementList()->begin(), 
		a->composition()->elementList()->end());
}
}
