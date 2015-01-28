#ifndef PD2MO_RANGE
#define PD2MO_RANGE
#include <../src/traverser.h>
#include <map>
#include <list>

namespace pd2mo{
class range: public Traverser {
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference); // AST_Expression
};
}
#endif 
