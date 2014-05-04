#include <pd2mo.h>

using namespace std;

namespace pd2mo{
Pd2Mo::Pd2Mo(){ 
	classMap = new map<string, string>();
	pd2mo_dir = getFullPath();
}

char * Pd2Mo::getFullPath(){
	char szTmp[320];
	char pBuf[320];
	int len = 320;
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = readlink(szTmp, pBuf, len);
	if(bytes >= 0)
		pBuf[bytes] = '\0';
	return dirname(pBuf);
}

void Pd2Mo::loadConfigFile(string file){
	//Class Mapping
	//Model Parameters
}
void Pd2Mo::transoform(string filename, ofstream output, ofstream log){

	QString qfilename = QString::fromStdString(filename);
	
        modelCoupled *model = parsePDS( qfilename);
	//Load class based on the coupledModel from file
	// AST_ClassList classList= getAsClassList(model, classMap); 

	//Rename each AST_Class variable based on name and position in the coupledmodel
	// AST_ClassListIterator it;

	//Add coupledmodel connections
	//Move all AST_Class List to a new "Model"
}

/**

*/
AST_ClassList Pd2Mo::getAsClassList(modelCoupled * c, map<string, string> * m){
	QList< modelChild * >::iterator childsIterator;
	AST_ClassList st = new list<AST_Class>();
	int r;
	for (childsIterator = c->childs.begin(); 
		childsIterator != c->childs.end(); 
		++childsIterator){
		modelChild * modelC = *childsIterator;
		if(m->count(modelC->atomic->path.toStdString())>0){
			AST_StoredDefinition sd = parseFile(
				(*m)[modelC->atomic->path.toStdString()],&r);
			st->insert(st->end(), sd->models()->begin(), sd->models()->end());
		}
	}
	return st;
}
}
