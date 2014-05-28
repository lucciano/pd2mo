#ifndef PD2MO_SET_PARAMS
#define PD2MO_SET_PARAMS
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <prefixmovars.h>
#include <traverser.h>
#include <iostream>
#include <QStringList>
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <simpd/pdevslib.h>
#include <string>

#define debug_out std::cout 

using namespace std;

namespace pd2mo{
class SetParameters: public Traverser {
    AST_ExpressionList exp;
    string paramsName;
    public: 
	void setParametersList(QStringList x);
	void setParameterName(string x){ paramsName = x; }
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

};
}

#endif
