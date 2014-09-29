#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
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

BOOST_AUTO_TEST_CASE( annon ){
    string path = getFullPath();
    string filename = path + "/data/qss_integrator_vec.mo";
    int r = 0;

    AST_StoredDefinition sd = parseFile(filename, &r);

    cout << "r : " << r << endl;
    AST_ClassList classList = sd->models();
    cout << "size : "<< classList->size() << endl;
}
