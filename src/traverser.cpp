#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
AST_StoredDefinition Traverser::visitStoredDefinition(AST_StoredDefinition sd){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassList models = sd->models();
	this->visitClassList(models);
	return sd;
}

AST_ClassList Traverser::visitClassList(AST_ClassList classList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassListIterator it;
	foreach(it, classList){
		this->visitClass(current_element(it));
	}
	return classList;
}

AST_Class Traverser::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << endl  ;
	this->visitComposition(_class->composition());

	AST_CompositionElementList compList = _class->composition()->compositionList();
	AST_CompositionElementListIterator compIt;
	foreach(compIt, compList){
		AST_EquationList eql = current_element(compIt)->getEquationsAlgs()->getEquations();
		this->visitEquationList(eql);
	}
	return _class;
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
		switch(current_element(it)->equationType()){
		//  case EQNONE:{
		//}
		  case EQEQUALITY:{
	AST_Equation_Equality eq = current_element(it)->getAsEquality();
	this->visitEquation_Equality(eq);
	break;	}
	//	  case EQCONNECT:{
	//AST_Equation_Connect eq = current_element(it)->getAsConnect();
	//this->visitEquation_Connect(eq);
	//break;	}
		  case EQCALL:{
	AST_Equation_Call eq = current_element(it)->getAsCall();
	this->visitEquation_Call(eq);
	break;	}
		  case EQFOR:{
	AST_Equation_For eq = current_element(it)->getAsFor();
	this->visitEquation_For(eq);
	break;	}
		  case EQWHEN:{
	AST_Equation_When eq = current_element(it)->getAsWhen();
	this->visitEquation_When(eq);
	break;	}
		  case EQIF:{
	AST_Equation_If eq = current_element(it)->getAsIf();
	this->visitEquation_If(eq);
	break;	}
		  default :
			throw current_element(it)->equationType();
		}
	}
	return eqList;
}

AST_Equation_Call Traverser::visitEquation_Call(AST_Equation_Call eqCall){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqCall;
}

AST_Equation_Connect Traverser::visitEquation_Connect(AST_Equation_Connect eqCon){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqCon;
}

AST_Equation_Equality Traverser::visitEquation_Equality(AST_Equation_Equality eqEq){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqEq;
}

AST_Equation_For Traverser::visitEquation_For(AST_Equation_For eqFor){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqFor;
}

AST_Equation_If Traverser::visitEquation_If(AST_Equation_If eqIf){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqIf;
}

AST_Equation_When Traverser::visitEquation_When(AST_Equation_When eqWhen){
	debug << __PRETTY_FUNCTION__ << endl  ;
	return eqWhen;
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
