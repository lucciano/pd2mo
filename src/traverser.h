#ifndef PD2MO_TRAVERSER
#define PD2MO_TRAVERSER
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>

namespace pd2mo{
class Traverser {
  public:
	Traverser(){};
	virtual AST_StoredDefinition visitStoredDefinition(AST_StoredDefinition st);
	virtual AST_String visitString(AST_String s);
	virtual AST_ClassList visitClassList(AST_ClassList classList);
	virtual AST_Class visitClass(AST_Class _class);
	virtual AST_Composition visitComposition(AST_Composition comp);
	virtual AST_EquationList visitEquationList(AST_EquationList eqList);

	virtual AST_Equation_Call visitEquation_Call(AST_Equation_Call eqCall);
	virtual AST_Equation_Connect visitEquation_Connect(AST_Equation_Connect eqCon);
	virtual AST_Equation_Equality visitEquation_Equality(AST_Equation_Equality eqEq);
	virtual AST_Equation_For visitEquation_For(AST_Equation_For eqFor);
	virtual AST_ForIndexList visitForIndexList(AST_ForIndexList forIndexList);
	virtual AST_ForIndex visitForIndex(AST_ForIndex forIndex);
	virtual AST_Equation_If visitEquation_If(AST_Equation_If eqIf);
	virtual AST_Equation_ElseList visitEquation_ElseList(AST_Equation_ElseList);
	virtual AST_Equation_Else visitEquation_Else(AST_Equation_Else);
	virtual AST_Equation_When visitEquation_When(AST_Equation_When eqWhen);

	virtual AST_ElementList visitElementList(AST_ElementList elementList);
	virtual AST_Element visitElement(AST_Element element); //AST_Element (type=NONE)
	virtual AST_Element_ClassWrapper visitElement_ClassWrapper(AST_Element_ClassWrapper cw); //AST_Element
	virtual AST_Element_Component visitElement_Component(AST_Element_Component comp); //AST_Element
	virtual AST_Element_ExtendsClause visitElement_ExtendsClause(AST_Element_ExtendsClause extends); //AST_Element
	virtual AST_Element_ImportClause visitElement_ImportClause(AST_Element_ImportClause import); //AST_Element
	virtual AST_DeclarationList visitDeclarationList(AST_DeclarationList decList);
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
	virtual AST_Modification visitModification(AST_Modification mod); //AST_Modification (type=MODNONE)
	virtual AST_Modification_Assign visitModification_Assign(AST_Modification_Assign modASsig); //AST_Modification 
	virtual AST_Modification_Class visitModification_Class(AST_Modification_Class modClass); //AST_Modification 
	virtual AST_Modification_Equal visitModification_Equal(AST_Modification_Equal modEq); //AST_Modification 
	virtual AST_Expression visitExpression(AST_Expression ex); //AST_Expression
	virtual AST_ExpressionList visitExpressionList(AST_ExpressionList ex); //AST_Expression
	virtual AST_Expression_BinOp visitExpression_BinOp(AST_Expression_BinOp); // AST_Expression
	virtual AST_Expression_Boolean visitExpression_Boolean(AST_Expression_Boolean); // AST_Expression
	virtual AST_Expression_BooleanNot visitExpression_BooleanNot(AST_Expression_BooleanNot); // AST_Expression
	virtual AST_Expression_Brace visitExpression_Brace(AST_Expression_Brace); // AST_Expression
	virtual AST_Expression_Call visitExpression_Call(AST_Expression_Call); // AST_Expression
	virtual AST_Expression_CallArgs visitExpression_CallArgs(AST_Expression_CallArgs); // AST_Expression
	virtual AST_Expression_Colon visitExpression_Colon(AST_Expression_Colon); // AST_Expression
	virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference); // AST_Expression
	virtual AST_Expression_Derivative visitExpression_Derivative(AST_Expression_Derivative); // AST_Expression
	virtual AST_Expression_End visitExpression_End(AST_Expression_End); // AST_Expression
	virtual AST_Expression_If visitExpression_If(AST_Expression_If); // AST_Expression
	virtual AST_Expression_If_ElseIf visitExpression_If_ElseIf(AST_Expression_If_ElseIf); // AST_Expression
	virtual AST_Expression_Integer visitExpression_Integer(AST_Expression_Integer); // AST_Expression
	virtual AST_Expression_Null visitExpression_Null(AST_Expression_Null); // AST_Expression
	virtual AST_Expression_Output visitExpression_Output(AST_Expression_Output); // AST_Expression
	virtual AST_Expression_Range visitExpression_Range(AST_Expression_Range); // AST_Expression
	virtual AST_Expression_Real visitExpression_Real(AST_Expression_Real); // AST_Expression
	virtual AST_Expression_String visitExpression_String(AST_Expression_String); // AST_Expression
	virtual AST_Expression_UMinus visitExpression_UMinus(AST_Expression_UMinus); // AST_Expression

	virtual AST_Element_ClassWrapper visitClassWrapper(AST_Element_ClassWrapper);
};
}
#endif
