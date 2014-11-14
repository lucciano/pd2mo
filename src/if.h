#ifndef PD2MO_IF
#define PD2MO_IF
#include <../src/traverser.h>
#include <map>
#include <list>

namespace pd2mo{
class If : public Traverser {
   public : 
	virtual AST_Statement_If visitStatement_If(AST_Statement_If stIf);
	virtual AST_Class visitClass(AST_Class _class);
};

}
#endif
