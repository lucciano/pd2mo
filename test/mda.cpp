#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <../src/mda.h>
#include <util/symbol_table.h>
#include <ast/class.h>
#include <mmo/mmo_class.h>



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
    string filename = "/home/powerdevs/pd2mo/test/data/eval.mo";
    int r = 0;
    TypeSymbolTable tyEnv = newTypeSymbolTable();
    AST_Class ast_c = parseClass(filename,&r);

    MMO_Class c = newMMO_Class(ast_c, tyEnv);
	cout << c ; 
}
