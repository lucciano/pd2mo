#ifndef PD2MO_TRAVERSER
#define PD2MO_TRAVERSER
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>

namespace pd2mo{
class Traverser {
  public:
	Traverser(){};
	virtual void visitStoredDefinition(AST_StoredDefinition st);
	virtual void visitClassList(AST_ClassList classList);
	virtual void visitClass(AST_Class _class);
	virtual void visitComposition(AST_Composition comp);
	virtual void visitEquationList(AST_EquationList eqList);

	virtual void visitEquation_Call(AST_Equation_Call eqCall);
	virtual void visitEquation_Connect(AST_Equation_Connect eqCon);
	virtual void visitEquation_Equality(AST_Equation_Equality eqEq);
	virtual void visitEquation_For(AST_Equation_For eqFor);
	virtual void visitEquation_If(AST_Equation_If eqIf);
	virtual void visitEquation_When(AST_Equation_When eqWhen);

	virtual void visitElementList(AST_ElementList elementList);
	virtual void visitElement(AST_Element element); //AST_Element (type=NONE)
	virtual void visitElement_ClassWrapper(AST_Element_ClassWrapper cw); //AST_Element
	virtual void visitElement_Component(AST_Element_Component comp); //AST_Element
	virtual void visitElement_ExtendsClause(AST_Element_ExtendsClause extends); //AST_Element
	virtual void visitElement_ImportClause(AST_Element_ImportClause import); //AST_Element
	virtual void visitDeclarationList(AST_DeclarationList decList);
	virtual void visitDeclaration(AST_Declaration dec);
	virtual void visitModification(AST_Modification mod); //AST_Modification (type=MODNONE)
	virtual void visitModification_Assign(AST_Modification_Assign modASsig); //AST_Modification 
	virtual void visitModification_Class(AST_Modification_Class modClass); //AST_Modification 
	virtual void visitModification_Equal(AST_Modification_Equal modEq); //AST_Modification 
	virtual void visitExpression(AST_Expression ex); //AST_Expression
	virtual void visitExpression_BinOp(AST_Expression_BinOp); // AST_Expression
	virtual void visitExpression_Boolean(AST_Expression_Boolean); // AST_Expression
	virtual void visitExpression_BooleanNot(AST_Expression_BooleanNot); // AST_Expression
	virtual void visitExpression_Brace(AST_Expression_Brace); // AST_Expression
	virtual void visitExpression_Call(AST_Expression_Call); // AST_Expression
	virtual void visitExpression_CallArgs(AST_Expression_CallArgs); // AST_Expression
	virtual void visitExpression_Colon(AST_Expression_Colon); // AST_Expression
	virtual void visitExpression_ComponentReference(AST_Expression_ComponentReference); // AST_Expression
	virtual void visitExpression_Derivative(AST_Expression_Derivative); // AST_Expression
	virtual void visitExpression_End(AST_Expression_End); // AST_Expression
	virtual void visitExpression_If(AST_Expression_If); // AST_Expression
	virtual void visitExpression_If_ElseIf(AST_Expression_If_ElseIf); // AST_Expression
	virtual void visitExpression_Integer(AST_Expression_Integer); // AST_Expression
	virtual void visitExpression_Null(AST_Expression_Null); // AST_Expression
	virtual void visitExpression_Output(AST_Expression_Output); // AST_Expression
	virtual void visitExpression_Range(AST_Expression_Range); // AST_Expression
	virtual void visitExpression_Real(AST_Expression_Real); // AST_Expression
	virtual void visitExpression_String(AST_Expression_String); // AST_Expression
	virtual void visitExpression_UMinus(AST_Expression_UMinus); // AST_Expression

	virtual void visitClassWrapper(AST_Element_ClassWrapper);
};
}
#endif
