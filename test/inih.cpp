#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <cstring>
#include <../inih/cpp/INIReader.h>

using namespace std;


BOOST_AUTO_TEST_CASE( cero ){
    cout << "cero" << endl;
    string path = getFullPath();
    INIReader reader(path + "/data/test.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'test.ini'\n";
    }else{
    std::cout << "Config loaded from 'test.ini': version="
              << reader.GetInteger("protocol", "version", -1) << ", name="
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", pi="
              << reader.GetReal("user", "pi", -1) << ", active="
              << reader.GetBoolean("user", "active", true) << "\n";
    }
}
BOOST_AUTO_TEST_CASE( uno ){
    cout << "uno" << endl;

    string path = getFullPath();
    INIReader reader(path + "/../data/pd2mo.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load file\n";
    }
}
