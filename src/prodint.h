#ifndef PD2MO_PRODINT
#define PD2MO_PRODINT
#include <../src/traverser.h>
#include <mmo/mmo_class.h>
namespace pd2mo{

class prodint : public Traverser {
	MMO_Class _c_class; 
   public:
	virtual AST_Expression visitExpression(AST_Expression); // AST_Expression
	virtual AST_Class visitClass(AST_Class _class);
};
}

#endif
