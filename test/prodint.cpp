#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <../src/mda.h>
#include <../src/prodint.h>
#include <ast/class.h>
#include <util/symbol_table.h>
#include <mmo/mmo_class.h>

using namespace std;
using namespace pd2mo;

BOOST_AUTO_TEST_CASE(product_interno){
    string filename = "/home/ubuntu/pd2mo/test/data/mda.mo";
    int r = 0;
    AST_StoredDefinition sd = parseFile(filename,&r);

    prodint *p = new prodint();
    cout << p->visitClass(*sd->models()->begin()) << endl;

}

