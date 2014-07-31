#include <fstream>
#include <pdppt/modelcoupled.h>

using namespace std;

class flatter {
	static modelCoupled * flat1l(modelCoupled * c);
	static int writePDS(modelCoupled * c, ofstream *o, int indent , string coordinator_type);
    public:
	static modelCoupled * flat(modelCoupled * c){
		bool needFlat = false;
		while(true){
		for (QList< modelChild * >::iterator childsIterator = c->childs.begin(); 
			childsIterator != c->childs.end(); 
			++childsIterator){

			if((*childsIterator)->childType == COUPLED){
				needFlat = true;
			}
		}
		if(needFlat) c = flatter::flat1l(c);
		else return c;
		}
	}

	static int writePDS(modelCoupled * c, ofstream *o){
		return writePDS(c, o, 0, string("Root-Coordinator"));
	}
};
