#include <fstream>
#include <pdppt/modelcoupled.h>

using namespace std;

class flatter {
    public:
	static modelCoupled * flat(modelCoupled * c);
	static int writePDS(modelCoupled * c, ofstream *o, int indent , string coordinator_type);
	static int writePDS(modelCoupled * c, ofstream *o){
		return writePDS(c, o, 0, string("Root-Coordinator"));
	}
};
