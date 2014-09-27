#include <motools.h>
#include <list>

using namespace std;

MoTool::MoTool(AST_Class c){
	_class = c;
}
AST_ExpressionList MoTool::getDimension(AST_String){
	AST_ExpressionList rtr = new std::list<AST_Expression_*>();
	return rtr;
}
