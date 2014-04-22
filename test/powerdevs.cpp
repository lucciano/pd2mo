#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <QFile>
#include <pdppt/parser.h>
#include <pdppt/modelcoupled.h>
#include <iostream>
#include <algorithm>  
#include <test/file_util.h>

using namespace std;

BOOST_AUTO_TEST_CASE( cero ) {

    BOOST_CHECK( 1 == 1 );
    QString path = getFullPath();
    QString filename = path + "/data/simple01.pds";
    modelCoupled *c = NULL;
    c = parsePDS(filename);
    cout << filename.toStdString() << endl;
    QList< modelChild * >::iterator childsIterator;
    for (childsIterator = c->childs.begin(); childsIterator != c->childs.end(); ++childsIterator){
	modelChild * modelC = *childsIterator;

        BOOST_CHECK(modelC->childType == ATOMIC  );
	cout << modelC->atomic->path.toStdString() << endl;
    }
}
