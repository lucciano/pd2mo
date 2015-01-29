#ifndef PD2MO_MDA
#define PD2MO_MDA
#include <../src/traverser.h>
#include <map>
#include <list>

namespace pd2mo{
class mda : public Traverser {
   std::map<string, AST_ExpressionList > def;

   std::map<string, AST_DeclarationList> declr;
   std::map<string, AST_Expression_Integer> var;

   AST_Expression lookUpVar(AST_Expression);

   public : 
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);

	virtual AST_Expression visitExpression(AST_Expression ex);

	virtual AST_ElementList visitElementList(AST_ElementList elementList);

};

}
#endif
