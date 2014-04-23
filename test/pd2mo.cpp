#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <string>
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
    BOOST_CHECK( 1 == 1 );
    int r = 0;
    string path = getFullPath();
    string filename = path + "/data/Constant.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    T1 t = T1();
    t.visitStoredDefinition(sd);
}

BOOST_AUTO_TEST_CASE( uno ){
    int r = 0;
    string path = getFullPath();
   // string filename = path + "/data/simple01.pds";
    string filename = path + "/data/Constant.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    T1 t = T1();
    t.visitStoredDefinition(sd);
}
