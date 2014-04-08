#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <QFile>
#include <pdppt/parser.h>
#include <pdppt/modelcoupled.h>


BOOST_AUTO_TEST_CASE( cero ) {
    BOOST_CHECK( 1 == 1 );
    QString filename = "data/simple01.pds";
    modelCoupled *c = NULL;
    c = parsePDS(filename);

}
