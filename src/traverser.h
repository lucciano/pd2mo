#ifndef PD2MO_TRAVERSER
#define PD2MO_TRAVERSER
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <util/symbol_table.h>

namespace pd2mo{
class Traverser {
  public:
	Traverser(){};
	virtual void visit(AST_StoredDefinition st);
	virtual void visit(AST_ClassList classList);
	virtual void visit(AST_Class _class);
	virtual void visit(AST_Composition comp);
	virtual void visit(AST_EquationList eqList);

	virtual void visit(AST_Equation_Call eqCall);
	virtual void visit(AST_Equation_Connect eqCon);
	virtual void visit(AST_Equation_Equality eqEq);
	virtual void visit(AST_Equation_For eqFor);
	virtual void visit(AST_Equation_If eqIf);
	virtual void visit(AST_Equation_When eqWhen);

	virtual void visit(AST_ElementList elementList);
	virtual void visit(AST_Element element); //AST_Element (type=NONE)
	virtual void visit(AST_Element_ClassWrapper cw); //AST_Element
	virtual void visit(AST_Element_Component comp); //AST_Element
	virtual void visit(AST_Element_ExtendsClause extends); //AST_Element
	virtual void visit(AST_Element_ImportClause import); //AST_Element
	virtual void visit(AST_DeclarationList decList);
	virtual void visit(AST_Declaration dec);
	virtual void visit(AST_Modification mod); //AST_Modification (type=MODNONE)
	virtual void visit(AST_Modification_Assign modASsig); //AST_Modification 
	virtual void visit(AST_Modification_Class modClass); //AST_Modification 
	virtual void visit(AST_Modification_Equal modEq); //AST_Modification 
	virtual void visit(AST_Expression ex); //AST_Expression
	virtual void visit(AST_Expression_BinOp); // AST_Expression
	virtual void visit(AST_Expression_Boolean); // AST_Expression
	virtual void visit(AST_Expression_BooleanNot); // AST_Expression
	virtual void visit(AST_Expression_Brace); // AST_Expression
	virtual void visit(AST_Expression_Call); // AST_Expression
	virtual void visit(AST_Expression_CallArgs); // AST_Expression
	virtual void visit(AST_Expression_Colon); // AST_Expression
	virtual void visit(AST_Expression_ComponentReference); // AST_Expression
	virtual void visit(AST_Expression_Derivative); // AST_Expression
	virtual void visit(AST_Expression_End); // AST_Expression
	virtual void visit(AST_Expression_If); // AST_Expression
	virtual void visit(AST_Expression_If_ElseIf); // AST_Expression
	virtual void visit(AST_Expression_Integer); // AST_Expression
	virtual void visit(AST_Expression_Null); // AST_Expression
	virtual void visit(AST_Expression_Output); // AST_Expression
	virtual void visit(AST_Expression_Range); // AST_Expression
	virtual void visit(AST_Expression_Real); // AST_Expression
	virtual void visit(AST_Expression_String); // AST_Expression
	virtual void visit(AST_Expression_UMinus); // AST_Expression
};
}
#endif
