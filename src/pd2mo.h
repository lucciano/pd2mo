#ifndef PD2MO_MAIN
#define PD2MO_MAIN
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <libgen.h>
#include <map>
#include <list>

#include <ast/stored_definition.h>
#include <ast/ast_types.h>
#include <ast/expression.h>
#include <parser/parse.h>
#include <pdppt/parser.h>
#include <pdppt/modelcoupled.h>

#include <sstream>
#include <prefixmovars.h>
#include <setParameters.h>



using namespace std;

namespace pd2mo{

enum tConnect {SCALAR, VECTORIAL};
typedef pair <tConnect,tConnect> tConnection;

string getFullPath();
class Pd2Mo {

	map<string, string> * classMap;
	map<string, string> * sourceType;
	map<int, string> modelSource;
	string pd2mo_dir;


	AST_ClassList getAsClassList(modelCoupled *, map<string, string> *, ostream * log);
	void Combine(AST_ElementList elem, 
				AST_StatementList initialStList, 
				AST_EquationList initialEqList, 
				AST_StatementList stList, 
				AST_EquationList eqList, AST_Class a);
	void setModelParameters(modelCoupled *, AST_ClassList);
	string makeMoFileName(string );
	
	list<tConnection> getClassConnections(AST_ClassList);

public:
	Pd2Mo();
	void transform(string file, ostream * output, ostream * log);
	void setPath(string);

};

void find_and_replace(string& source, string const& find, string const& replace);
}

#endif
