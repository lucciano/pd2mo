#ifndef PD2MO_MDA
#define PD2MO_MDA
#include <../src/traverser.h>
#include <map>
#include <list>

namespace pd2mo{
class mda : public Traverser {
   std::map<string, AST_ExpressionList > def;

   std::map<string, AST_Declaration> declr;
   std::map<string, AST_Expression_Integer> var;
   public : 
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);

	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

	virtual AST_DeclarationList visitDeclarationList(AST_DeclarationList decList);
};
}
#endif
