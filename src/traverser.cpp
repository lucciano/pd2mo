#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
AST_StoredDefinition Traverser::visitStoredDefinition(AST_StoredDefinition sd){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_StoredDefinition_ (this->visitClassList(sd->models()), 
			       this->visitString(sd->within()));
}

AST_String Traverser::visitString(AST_String s){
	return s;
}

AST_ClassList Traverser::visitClassList(AST_ClassList classList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassListIterator it;
	foreach(it, classList){
		current_element(it) = this->visitClass(current_element(it));
	}
	return classList;
}

AST_Class Traverser::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Class_ (this->visitString(_class->name()), 
			this->visitComposition(_class->composition()));
	//AST_CompositionElementList compList = _class->composition()->compositionList();
	//AST_CompositionElementListIterator compIt;
	//foreach(compIt, compList){
	//	AST_EquationList eql = current_element(compIt)->getEquationsAlgs()->getEquations();
	//	this->visitEquationList(eql);
	//}
	//return _class;
}

AST_Composition Traverser::visitComposition(AST_Composition comp){
	debug << __PRETTY_FUNCTION__ << endl ;
	AST_ElementList elList = comp->elementList();
	this->visitElementList(elList);
	return comp;
}

AST_EquationList Traverser::visitEquationList(AST_EquationList eqList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_EquationListIterator it;
	foreach(it, eqList){
		switch(current_element(it)->equationType()){ //TODO: este switch deberia estar dentro de visitEquation ¿no?
		  case EQEQUALITY:{
	AST_Equation_Equality eq = current_element(it)->getAsEquality();
		current_element(it) = this->visitEquation_Equality(eq);
	break;	}
	//	  case EQCONNECT:{
	//AST_Equation_Connect eq = current_element(it)->getAsConnect();
	//this->visitEquation_Connect(eq);
	//break;	}
		  case EQCALL:{
	AST_Equation_Call eq = current_element(it)->getAsCall();
		current_element(it) = this->visitEquation_Call(eq);
	break;	}
		  case EQFOR:{
	AST_Equation_For eq = current_element(it)->getAsFor();
		current_element(it) = this->visitEquation_For(eq);
	break;	}
		  case EQWHEN:{
	AST_Equation_When eq = current_element(it)->getAsWhen();
		current_element(it) = this->visitEquation_When(eq);
	break;	}
		  case EQIF:{
	AST_Equation_If eq = current_element(it)->getAsIf();
		current_element(it) = this->visitEquation_If(eq);
	break;	}
		  case EQNONE:
		  default :
			throw current_element(it)->equationType();
		}
	}
	return eqList;
}

AST_Equation_Call Traverser::visitEquation_Call(AST_Equation_Call eqCall){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_Call_ (this->visitExpression(eqCall->call()));
}

AST_Equation_Connect Traverser::visitEquation_Connect(AST_Equation_Connect eqCon){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_Connect_ (
		this->visitExpression_ComponentReference(eqCon->left()),
		this->visitExpression_ComponentReference(eqCon->right()));
}

AST_Equation_Equality Traverser::visitEquation_Equality(AST_Equation_Equality eqExp){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_Equality_ (
		this->visitExpression(eqExp->left()), 
		this->visitExpression(eqExp->right()));
}

AST_Equation_For Traverser::visitEquation_For(AST_Equation_For eqFor){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_For_ (
		visitForIndexList(eqFor->forIndexList()),
		visitEquationList(eqFor->equationList()));
}

AST_ForIndexList Traverser::visitForIndexList(AST_ForIndexList forIndexList){
	debug << __PRETTY_FUNCTION__ << endl;
	AST_ForIndexListIterator it;
	foreach(it, forIndexList){
		current_element(it) = visitForIndex(current_element(it));
	}
	return forIndexList;
}

AST_ForIndex Traverser::visitForIndex(AST_ForIndex forIndex){
	debug << __PRETTY_FUNCTION__ << endl;
	return new AST_ForIndex_ (visitString(forIndex->variable()), 
				  visitExpression(forIndex->in_exp()));
}

AST_Equation_If Traverser::visitEquation_If(AST_Equation_If eqIf){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_If_ (
		visitExpression(eqIf->condition()),
		visitEquationList(eqIf->equationList()),
		visitEquation_ElseList(eqIf->equationElseIf()),
		visitEquationList(eqIf->equationElseList())
		);
}

AST_Equation_ElseList Traverser::visitEquation_ElseList(AST_Equation_ElseList elseList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_Equation_ElseListIterator it;
	foreach(it, elseList){
		current_element(it) = visitEquation_Else(current_element(it));
	}
	return elseList;
}

AST_Equation_Else Traverser::visitEquation_Else(AST_Equation_Else _else){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return new AST_Equation_Else_(
		visitExpression(_else->condition()), 
		visitEquationList(_else->equations()));
}

AST_Equation_When Traverser::visitEquation_When(AST_Equation_When eqWhen){
	debug << __PRETTY_FUNCTION__ << endl;
	return new AST_Equation_When_ (
		visitExpression(eqWhen->condition()),
		visitEquationList(eqWhen->equationList()), 
		visitEquation_ElseList(eqWhen->equationElseWhen()));
}

AST_ElementList Traverser::visitElementList(AST_ElementList elementList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ElementListIterator elIt;
	foreach(elIt, elementList){
		switch(current_element(elIt)->elementType()){
		case COMPONENT:{
			AST_Element_Component el = current_element(elIt)->getAsComponent();
			this->visitElement_Component(el);
			break;
		}
		case IMPORT: {
			AST_Element_ImportClause el = current_element(elIt)->getAsImportClause();
			this->visitElement_ImportClause(el);
			break;
		}
		case EXTENDS: {
			AST_Element_ExtendsClause el = current_element(elIt)->getAsExtendsClause();
			this->visitElement_ExtendsClause(el);
			break;
		}
		case ELCLASS: {
			AST_Element_ClassWrapper el = current_element(elIt)->getAsClassWrapper();
			this->visitClassWrapper(el);
			break;
		}
		case ELNONE:
		default:
			throw current_element(elIt)->elementType();
		}
        }

	return elementList;
}

AST_Element Traverser::visitElement(AST_Element element){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return element;
}

AST_Element_ClassWrapper Traverser::visitElement_ClassWrapper(AST_Element_ClassWrapper cw){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
	return cw;
}

AST_Element_Component Traverser::visitElement_Component(AST_Element_Component comp){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_DeclarationList  decl = comp->nameList ();
	this->visitDeclarationList(decl);
	return comp;
}

AST_Element_ExtendsClause Traverser::visitElement_ExtendsClause(AST_Element_ExtendsClause extends){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
	return extends;
}

AST_Element_ImportClause Traverser::visitElement_ImportClause(AST_Element_ImportClause import){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return import;
}

AST_DeclarationList Traverser::visitDeclarationList(AST_DeclarationList decList){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_DeclarationListIterator it;
	foreach(it, decList){
		this->visitDeclaration(current_element(it));
	}
	return decList;
}

AST_Declaration Traverser::visitDeclaration(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_Modification modif = dec->modification();
	if(modif){
		switch(modif->modificationType()){
		case MODEQUAL:{
			AST_Modification_Equal mo = modif->getAsEqual();
			this->visitModification_Equal(mo);
			break;
		}
		case MODASSIGN:{
			AST_Modification_Assign mo = modif->getAsAssign();
			this->visitModification_Assign(mo);
			break;
		}
		case MODCLASS:{
			AST_Modification_Class mo = modif->getAsClass();
			this->visitModification_Class(mo);
			break;
		}
		case  MODNONE:
		default:
			throw modif->modificationType();
		}
	}
	return dec;
}

AST_Modification Traverser::visitModification(AST_Modification mod){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return mod;
}

AST_Modification_Assign Traverser::visitModification_Assign(AST_Modification_Assign modASsig){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return modASsig;
}

AST_Modification_Class Traverser::visitModification_Class(AST_Modification_Class modClass){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return modClass;
}

AST_Modification_Equal Traverser::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	this->visitExpression(modEq->exp());
	return modEq;
}

AST_ExpressionList Traverser::visitExpressionList(AST_ExpressionList exList){
	return exList;
}
AST_Expression Traverser::visitExpression(AST_Expression ex){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return ex;
}

AST_Expression_BinOp Traverser::visitExpression_BinOp(AST_Expression_BinOp binOp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return binOp;
}

AST_Expression_Boolean Traverser::visitExpression_Boolean (AST_Expression_Boolean boolean){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return boolean;
}

AST_Expression_BooleanNot Traverser::visitExpression_BooleanNot(AST_Expression_BooleanNot notExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return notExp;
}

AST_Expression_Brace Traverser::visitExpression_Brace(AST_Expression_Brace brace){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return brace;
}

AST_Expression_Call Traverser::visitExpression_Call(AST_Expression_Call callExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return callExp;
}

AST_Expression_CallArgs Traverser::visitExpression_CallArgs(AST_Expression_CallArgs callArgsExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return callArgsExp;
}

AST_Expression_Colon Traverser::visitExpression_Colon(AST_Expression_Colon colonExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return colonExp;
}

AST_Expression_ComponentReference Traverser::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return compRefExp;
}

AST_Expression_Derivative Traverser::visitExpression_Derivative(AST_Expression_Derivative der){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return der;
}

AST_Expression_End Traverser::visitExpression_End(AST_Expression_End endStm){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return endStm;
}

AST_Expression_If Traverser::visitExpression_If(AST_Expression_If ifExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return ifExp;
}

AST_Expression_If_ElseIf Traverser::visitExpression_If_ElseIf(AST_Expression_If_ElseIf elseIfExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return elseIfExp;
}

AST_Expression_Integer Traverser::visitExpression_Integer(AST_Expression_Integer expInt){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return expInt;
}

AST_Expression_Null Traverser::visitExpression_Null(AST_Expression_Null nullExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return nullExp;
}

AST_Expression_Output Traverser::visitExpression_Output(AST_Expression_Output outExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return outExp;
}

AST_Expression_Range Traverser::visitExpression_Range(AST_Expression_Range rangeExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return rangeExp;
}

AST_Expression_Real Traverser::visitExpression_Real(AST_Expression_Real realExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return realExp;
}

AST_Expression_String Traverser::visitExpression_String(AST_Expression_String strExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return strExp;
}

AST_Expression_UMinus Traverser::visitExpression_UMinus(AST_Expression_UMinus uminusExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return uminusExp;
}

AST_Element_ClassWrapper Traverser::visitClassWrapper(AST_Element_ClassWrapper classWrapExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	return classWrapExp;
}

}
