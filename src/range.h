#ifndef PD2MO_RANGE
#define PD2MO_RANGE
#include <../src/traverser.h>
#include <map>
#include <list>
#include <mmo/mmo_class.h>

namespace pd2mo{
class range: public Traverser {
   public:
	MMO_Class _c_class; 
	virtual AST_Expression visitExpression(AST_Expression); // AST_Expression
	virtual AST_Class visitClass(AST_Class _class);
};
}
#endif 
