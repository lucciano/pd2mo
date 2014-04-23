#ifndef PD2MO_PREFIXMOVARS
#define PD2MO_PREFIXMOVARS
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <traverser.h>

namespace pd2mo{
class PrefixMoVars: public Traverser {
	virtual void visitModification_Equal(AST_Modification_Equal modEq);
	virtual void visitDeclaration(AST_Declaration dec);
	virtual void visitClass(AST_Class _class);
};
}
#endif
