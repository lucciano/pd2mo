#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <../src/pd2mo.h>
#include <string>
#include <sstream>
#include <../src/prefixmovars.h>
#include <../src/traverser.h>

#include <QFile>
#include <pdppt/parser.h>
#include <pdppt/modelcoupled.h>
#include <map>
#include <ast/expression.h>


#define debug std::cout 

using namespace std;
using namespace pd2mo;

class T1: public Traverser {
public:
	virtual AST_Modification_Equal visitModification_Equal(AST_Modification_Equal modEq);
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Class visitClass(AST_Class _class);
};

AST_Class T1::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << _class->name() << endl  ; 
	return Traverser::visitClass(_class);
}

AST_Declaration T1::visitDeclaration(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << dec->name() << endl  ; 
	AST_ExpressionListIterator it;
	foreach(it, dec->indexes()){
		cout <<"Indices " << current_element(it) << endl;
	}
	return Traverser::visitDeclaration(dec);
}
AST_Modification_Equal T1::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << modEq << endl  ; 
	Traverser::visitExpression(modEq->exp());
	return modEq;
}

BOOST_AUTO_TEST_CASE( cero ) {
    cout << "cero" << endl;
    BOOST_CHECK( 1 == 1 );
    int r = 0;
    string path = getFullPath();
    string filename = path + "/data/qss/qss_wsum.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    T1 t = T1();
    t.visitStoredDefinition(sd);
    cout << current_element(sd->models()->begin())->prefix() <<endl;
}

BOOST_AUTO_TEST_CASE( uno ){
    cout << "uno" << endl;
    int r = 0;
    string path = getFullPath();
   // string filename = path + "/data/simple01.pds";
    string filename = path + "/data/Constant.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    PrefixMoVars p = PrefixMoVars();
    p.setPrefix("constant_N_");
    AST_StoredDefinition sd2 = p.visitStoredDefinition(sd);
    cout << sd << endl;
}

AST_Class Combine(AST_String name, AST_Class a, AST_Class b){

	AST_CompositionElementList comp = new list<AST_CompositionElement>();
	AST_ElementList elem = new list<AST_Element>();

	AST_Composition composition = new AST_Composition_ (elem, comp);
	AST_Class ret = new AST_Class_(name, composition);
	AST_StatementList stList = new list<AST_Statement>();
	AST_EquationList eqList = new list<AST_Equation>();

	AST_CompositionEqsAlgs eqAlgsST = new AST_CompositionEqsAlgs_(stList);
	AST_CompositionEqsAlgs eqAlgsEQ = new AST_CompositionEqsAlgs_(eqList);

	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsST));
	comp->insert(comp->end(), new AST_CompositionElement_(eqAlgsEQ));

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
	foreach(it, b->composition()->compositionList()){
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

	elem->insert(elem->end(), 
		b->composition()->elementList()->begin(), 
		b->composition()->elementList()->end());

	ret->setPrefixes(CP_MODEL);
	return ret;
}

BOOST_AUTO_TEST_CASE( dos ){
    cout << "dos" << endl;
    string path = getFullPath();
    string filename = path + "/data/Constant.mo";
    int r = 0;
    AST_StoredDefinition sd1 = parseFile(filename,&r);

    PrefixMoVars pa = PrefixMoVars();
    pa.setPrefix("constant_X_");
    AST_StoredDefinition sda = pa.visitStoredDefinition(sd1);

    PrefixMoVars pb = PrefixMoVars();
    pb.setPrefix("constant_N_");
    AST_StoredDefinition sd2 = parseFile(filename,&r);
    AST_StoredDefinition sdb = pb.visitStoredDefinition(sd2);

    AST_String name = new  string("Model01");
    cout << Combine(name, current_element(sdb->models()->begin()),
		current_element(sda->models()->begin())) << endl;

}

AST_ClassList getAsClassList(modelCoupled * c, map<string, string> m){
	QList< modelChild * >::iterator childsIterator;
	AST_ClassList st = new list<AST_Class>();
	int r;
	for (childsIterator = c->childs.begin(); 
		childsIterator != c->childs.end(); 
		++childsIterator){
		modelChild * modelC = *childsIterator;
		if(m.count(modelC->atomic->path.toStdString())>0){
			AST_StoredDefinition sd = parseFile(
				m[modelC->atomic->path.toStdString()],&r);
			st->insert(st->begin(), sd->models()->begin(), sd->models()->end());
		}
	}
	return st;
}

BOOST_AUTO_TEST_CASE( tres ){
    cout << "tres" << endl;
    QString path = getFullPath();
    QString filename = path + "/data/simple01.pds";
    int r = 0; 
    map<string, string> classMap;
    classMap["qss/qss_integrator.h"] = path.toStdString() + "/data/Constant.mo";
    classMap["qss/qss_wsum.h"] = path.toStdString() + "/data/Constant.mo";
    classMap["sources\\constant_sci.h"] = path.toStdString() + "/data/Constant.mo";

    modelCoupled *c = parsePDS(filename);
    AST_ClassList cl = getAsClassList(c, classMap);
    AST_ClassListIterator it; 
    foreach(it, cl){
	cout << current_element(it) << endl;
    }

    QList<modelConnection*> * lsIc = &(c->lsIC);
    QList<modelConnection*>::iterator itM;

    QList<modelChild * > * childs = &(c->childs);
    map<string, int> sourceArray;
    sourceArray["qss/qss_integrator.h"] = 0;
    sourceArray["qss/qss_wsum.h"] = 1; // Input Array...
    sourceArray["sources\\constant_sci.h"] = 0;


    foreach(itM, lsIc){
	modelChild * srcModel = childs->at(current_element(itM)->childSource);
	modelChild * sinkModel = childs->at(current_element(itM)->childSink);
	cout << srcModel->atomic->path.toStdString()
		<< "(" << current_element(itM)->sourcePort << ")-->"
		<< sinkModel->atomic->path.toStdString() 
		<< "(" << current_element(itM)->sinkPort << ")" << endl;

        AST_ExpressionList lt1 = new list<AST_Expression>();
        AST_ExpressionList lt2 = new list<AST_Expression>();
	stringstream sincStream; sincStream << current_element(itM)->childSink << "_u";
	stringstream sourceStream; sourceStream<< current_element(itM)->childSource << "_y";
        AST_String source = new string(sincStream.str());
        AST_String sink = new string(sourceStream.str());
        AST_Expression_ComponentReference esource = 
            new AST_Expression_ComponentReference_ ();
        AST_Expression_ComponentReference esink = 
            new AST_Expression_ComponentReference_ ();
        esink->append(sink, lt1);
        esource->append(source, lt2);
        AST_Equation_Equality eq = new AST_Equation_Equality_(esource, esink);
        cout << eq << endl;

    }
}

BOOST_AUTO_TEST_CASE( cuatro ){
    cout << "cuatro" << endl;
    string path = getFullPath();
    string filename = path + "/data/simple01.pds";
    Pd2Mo q = Pd2Mo();
    q.transform(filename, &cout, &cout);
	cout << "fin.."<< endl;

    QString qfilename = QString::fromStdString(filename);
    modelCoupled *model = parsePDS(qfilename);
    QList<modelChild * >::iterator itC;
    QList<modelChild * > * childs = &(model->childs);
    foreach(itC, childs){
	modelAtomic * m = current_element(itC)->atomic;
	//cout << m->paramsString.toStdString();
	QStringList params = m->paramsString.split(',');
	QStringList * paramsp = &(params);
	QStringList::iterator itQs;
	foreach(itQs, paramsp){
		cout << current_element(itQs).toStdString() << endl;
	}
    }
}
