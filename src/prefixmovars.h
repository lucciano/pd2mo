#ifndef PD2MO_PREFIXMOVARS
#define PD2MO_PREFIXMOVARS
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <traverser.h>

namespace pd2mo{
class PrefixMoVars: public Traverser {
	virtual AST_Modification_Equal visitModification_Equal(AST_Modification_Equal modEq);
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Class visitClass(AST_Class _class);
};
}
#endif
