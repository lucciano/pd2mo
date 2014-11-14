#include <if.h>
using namespace pd2mo;
AST_Statement_If If::visitStatement_If(AST_Statement_If stIf){
	return Traverser::visitStatement_If(stIf);
}
AST_Class If::visitClass(AST_Class _class){
	return Traverser::visitClass(_class);
}
