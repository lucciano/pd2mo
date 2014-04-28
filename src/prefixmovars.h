#ifndef PD2MO_PREFIXMOVARS
#define PD2MO_PREFIXMOVARS
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <traverser.h>
#include <string>

namespace pd2mo{
class PrefixMoVars: public Traverser {
    string prefix;
    public: 
	void setPrefix(string x){ prefix = x; }
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);
};
}
#endif
