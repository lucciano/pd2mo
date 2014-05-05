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


using namespace std;

namespace pd2mo{
class Pd2Mo {

	map<string, string> * classMap;
	string pd2mo_dir;

	char * getFullPath();

	AST_ClassList getAsClassList(modelCoupled *, map<string, string> *, ostream * log);

public:
	Pd2Mo();
	void loadConfigFile(string file, ostream * log);
	void transform(string file, ostream * output, ostream * log);
};
}

#endif
