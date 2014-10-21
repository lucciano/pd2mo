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

   AST_Expression lookUpVar(AST_Expression);

   public : 
	virtual AST_EquationList visitEquationList(AST_EquationList eqList);

	virtual AST_Declaration visitDeclaration(AST_Declaration dec);

	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

	virtual AST_DeclarationList visitDeclarationList(AST_DeclarationList decList);

	virtual AST_Statement_For visitStatement_For(AST_Statement_For stFor);

	virtual AST_Expression visitExpression(AST_Expression ex);

};

}
#endif
