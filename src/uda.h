#ifndef PD2MO_UDA
#define PD2MO_UDA
#include <../src/traverser.h>
#include <map>
#include <list>

namespace pd2mo{
class uda : public Traverser {

   std::map<string, std::list<int>> var;

   public : 
	virtual AST_EquationList visitEquationList(AST_EquationList eqList);

	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

	virtual AST_DeclarationList visitDeclarationList(AST_DeclarationList decList);

	virtual AST_Statement_For visitStatement_For(AST_Statement_For stFor);

	virtual AST_Expression visitExpression(AST_Expression ex);

	virtual AST_ElementList visitElementList(AST_ElementList elementList);
};

}
#endif
