
#include <ast/expression.h>
#include <ast/class.h>


class MoTool{
public:
   MoTool(AST_Class);
   AST_ExpressionList getDimension(AST_String);
private:
   AST_Class _class;
};
