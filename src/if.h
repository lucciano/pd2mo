#ifndef PD2MO_IF
#define PD2MO_IF
#include <../src/traverser.h>
#include <map>
#include <list>
#include <mmo/mmo_class.h>

namespace pd2mo{
class If : public Traverser {
   MMO_Class _c_class;
   public : 
	virtual AST_EquationList visitEquationList(AST_EquationList eqList);
	virtual AST_Class visitClass(AST_Class _class);
};

}
#endif
