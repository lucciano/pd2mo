#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <string>
#include <ast/stored_definition.h>
#include "parser/parse.h"


BOOST_AUTO_TEST_CASE( cero ) {
    BOOST_CHECK( 1 == 1 );
    int r = 0;
    string path = getFullPath();
    string filename = path + "/data/Constant.mo";
    AST_StoredDefinition sd = parseFile(filename,&r);
    AST_ClassList models = sd->models();
}
