#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <string>
#include <../src/prefixmovars.h>
#include <../src/traverser.h>

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
    string filename = path + "/data/Constant.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    T1 t = T1();
    t.visitStoredDefinition(sd);
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

	/*Class
		-> Composition -> 
			->AST_CompositionElementList 	compositionList () const
				->  AST_CompositionEqsAlgs 	getEquationsAlgs ()
					-> AST_EquationList 	getEquations ()
					-> AST_StatementList 	getAlgorithms ()
					-> bool 	isInitial ()
				->  AST_ElementList 	getElementList ()
			->AST_ElementList 	elementList () const 
	*/

	comp->insert(comp->end(), 
		a->composition()->compositionList()->begin(), 
		a->composition()->compositionList()->end());
	
	comp->insert(comp->end(), 
		b->composition()->compositionList()->begin(), 
		b->composition()->compositionList()->end());

	elem->insert(elem->end(), 
		a->composition()->elementList()->begin(), 
		a->composition()->elementList()->end());

	elem->insert(elem->end(), 
		b->composition()->elementList()->begin(), 
		b->composition()->elementList()->end());

	return new AST_Class_(name, new AST_Composition_ (elem, comp));
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
