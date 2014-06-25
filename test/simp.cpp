#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <cstring>
#include <simpd/pdevslib.h>

using namespace std;

double tf = 0;

BOOST_AUTO_TEST_CASE( cero ){
	cout << getScilabVar("3.1416398") << endl;
}
