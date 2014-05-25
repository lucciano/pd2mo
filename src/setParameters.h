#ifndef PD2MO_SET_PARAMS
#define PD2MO_SET_PARAMS
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <prefixmovars.h>
#include <traverser.h>
#include <iostream>
#define debug std::cout 

using namespace std;

namespace pd2mo{
class SetParameters: public Traverser {
    list<string> params;
    string paramsName;
    public: 
	void setParameters(list<string> x){ params = x; }
	void setParameterName(string x){ paramsName = x; }
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

};
}

#endif
