#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <../src/mda.h>
#include <ast/class.h>
#include <util/symbol_table.h>
#include <mmo/mmo_class.h>
#include <../src/if.h>



using namespace std;
using namespace pd2mo;

BOOST_AUTO_TEST_CASE( multidimarray){

    //string path = getFullPath();
    string filename = "/home/powerdevs/pd2mo/test/data/mda.mo";
    int r = 0;
    AST_StoredDefinition sd = parseFile(filename,&r);

    mda *m = new mda();

    //cout << *sd->models()->begin() << endl;
     
    cout << m->visitClass(*sd->models()->begin()) << endl;

}

BOOST_AUTO_TEST_CASE( mmo ){
    string filename = "/home/powerdevs/pd2mo/test/data/EvalCondition.mo";
    int r = 0;
    TypeSymbolTable tyEnv = newTypeSymbolTable();
    AST_Class ast_c = parseClass(filename,&r);

    MMO_Class c = newMMO_Class(ast_c, tyEnv);
	cout << c ; 
  AST_Expression_Integer intExp =  (AST_Expression_Integer) newAST_Expression_Real(0.0);
  //AST_Expression_Integer intExp2 = (AST_Expression_Integer) newAST_Expression_Integer(2);
  AST_Expression_ComponentReference intExp2 = (AST_Expression_ComponentReference) newAST_Expression_ComponentReference();
  AST_String s = new std::string("shift");
  intExp2->append(s, new std::list<AST_Expression>());
  AST_Expression_BinOp binOp = (AST_Expression_BinOp) newAST_Expression_BinOp(intExp2, intExp, BINOPGREATER);

  EvalExp *evalExp = new EvalExp(c->getVarSymbolTable());
  AST_Expression result = evalExp->eval(binOp);
	cout << result << endl;
	cout << evalExp->eval(intExp2) << endl;
	cout << intExp << endl;
	cout << binOp << endl;

}

BOOST_AUTO_TEST_CASE( mmo2 ){
    string filename = "/home/powerdevs/pd2mo/test/data/EvalCondition.mo";
    int r = 0;
    TypeSymbolTable tyEnv = newTypeSymbolTable();
    AST_Class ast_c = parseClass(filename,&r);
    If * i =  new If();
    ast_c = i->visitClass(ast_c);
    cout << ast_c << endl;

}
