#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <src/flatter.h>
#include <pdppt/modelcoupled.h>
#include <pdppt/parser.h>
#include <QFile>
#include <test/file_util.h>


using namespace std;

BOOST_AUTO_TEST_CASE( cero ){
    QString path = getFullPath();
    QString filename = path + "/data/Coupled.pds";
    modelCoupled *c = parsePDS(filename);
    QList< modelChild * >::iterator childsIterator;
    for (childsIterator = c->childs.begin(); childsIterator != c->childs.end(); ++childsIterator){
    	modelChild * modelC = *childsIterator;
    
        if(modelC->childType == ATOMIC  ){
		cout << "CHILD"<< endl;
		cout << modelC->atomic->path.toStdString() << endl;
	}else if(modelC->childType == COUPLED) {
		cout << "COUPLED"<< "(" << modelC->coupled->childs.size() << ")" << endl;
	}else{
		cout << "NONO"<< endl;
	}
        }
}

BOOST_AUTO_TEST_CASE( uno ){
    cout << "------------------------------------\n";
    QString path = getFullPath();
    QString filename = path + "/data/Coupled.pds";
    modelCoupled *c = parsePDS(filename);
    cout <<"Type : " << c->type.toStdString() << " Name:" << c->name.toStdString() << endl;;

    cout << c->childs.size() << endl; //3 -> 4
    for(QList < modelConnection * >::iterator ic = c->lsIC.begin();
			ic != c->lsIC.end();
			ic++){
	cout << "(" << (*ic)->childSource << "," << (*ic)->sourcePort << ")" <<
		"(" << (*ic)->childSink << "," << (*ic)->sinkPort << ")" << endl;
    }

    modelCoupled *q = flatter::flat(c);
    cout << q->childs.size() << endl;

    QList< modelChild * >::iterator childsIterator;
    for (childsIterator = q->childs.begin(); childsIterator != q->childs.end(); ++childsIterator){
    	modelChild * modelC = *childsIterator;
        if(modelC->childType == ATOMIC  ){
		cout << "CHILD"<< endl;
		cout << modelC->atomic->path.toStdString() << endl;
	}else if(modelC->childType == COUPLED) {
		cout << "COUPLED"<< "(" << modelC->coupled->childs.size() << ")" << endl;
	}else{
		cout << "NONO"<< endl;
	}
    }

    for(QList < modelConnection * >::iterator ic = q->lsIC.begin();
			ic != q->lsIC.end();
			ic++){
	cout << "(" << (*ic)->childSource << "," << (*ic)->sourcePort << ")" <<
		"(" << (*ic)->childSink << "," << (*ic)->sinkPort << ")" << endl;
    }
}

