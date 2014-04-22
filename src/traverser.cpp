#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
void Traverser::visitStoredDefinition(AST_StoredDefinition sd){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassList models = sd->models();
	this->visitClassList(models);

}

void Traverser::visitClassList(AST_ClassList classList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassListIterator it;
	foreach(it, classList){
		this->visitClass(current_element(it));
	}
}

void Traverser::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << endl  ;
	this->visitComposition(_class->composition());

	AST_CompositionElementList compList = _class->composition()->compositionList();
	AST_CompositionElementListIterator compIt;
	foreach(compIt, compList){
		AST_EquationList eql = current_element(compIt)->getEquationsAlgs()->getEquations();
		this->visitEquationList(eql);
	}
}

void Traverser::visitComposition(AST_Composition comp){
	debug << __PRETTY_FUNCTION__ << endl ;
	AST_ElementList elList = comp->elementList();
	this->visitElementList(elList);
}

void Traverser::visitEquationList(AST_EquationList eqList){
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
}

void Traverser::visitEquation_Call(AST_Equation_Call eqCall){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitEquation_Connect(AST_Equation_Connect eqCon){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitEquation_Equality(AST_Equation_Equality eqEq){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitEquation_For(AST_Equation_For eqFor){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitEquation_If(AST_Equation_If eqIf){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitEquation_When(AST_Equation_When eqWhen){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitElementList(AST_ElementList elementList){
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

}

void Traverser::visitElement(AST_Element element){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitElement_ClassWrapper(AST_Element_ClassWrapper cw){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitElement_Component(AST_Element_Component comp){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_DeclarationList  decl = comp->nameList ();
	this->visitDeclarationList(decl);
}

void Traverser::visitElement_ExtendsClause(AST_Element_ExtendsClause extends){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visitElement_ImportClause(AST_Element_ImportClause import){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitDeclarationList(AST_DeclarationList decList){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_DeclarationListIterator it;
	foreach(it, decList){
		this->visitDeclaration(current_element(it));
	}
}

void Traverser::visitDeclaration(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_Modification modif = dec->modification();
	if(modif){
		switch(modif->modificationType()){
		case MODEQUAL:{
			AST_Modification_Equal mo = modif->getAsEqual();
			this->visitModification_Equal(mo);
			return ;
		}
		case MODASSIGN:{
			AST_Modification_Assign mo = modif->getAsAssign();
			this->visitModification_Assign(mo);
			return ;
		}
		case MODCLASS:{
			AST_Modification_Class mo = modif->getAsClass();
			this->visitModification_Class(mo);
			return ;
		}
		case  MODNONE:
		default:
			throw modif->modificationType();
		}
	}
}

void Traverser::visitModification(AST_Modification mod){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitModification_Assign(AST_Modification_Assign modASsig){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitModification_Class(AST_Modification_Class modClass){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	this->visitExpression(modEq->exp());
}

void Traverser::visitExpression(AST_Expression ex){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_BinOp(AST_Expression_BinOp binOp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Boolean (AST_Expression_Boolean boolean){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_BooleanNot(AST_Expression_BooleanNot notExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Brace(AST_Expression_Brace brace){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Call(AST_Expression_Call){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_CallArgs(AST_Expression_CallArgs){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Colon(AST_Expression_Colon){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_ComponentReference(AST_Expression_ComponentReference){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Derivative(AST_Expression_Derivative der){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_End(AST_Expression_End endStm){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_If(AST_Expression_If ifExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_If_ElseIf(AST_Expression_If_ElseIf elseIfExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Integer(AST_Expression_Integer){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Null(AST_Expression_Null nullExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Output(AST_Expression_Output outExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Range(AST_Expression_Range rangeExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_Real(AST_Expression_Real realExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_String(AST_Expression_String strExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitExpression_UMinus(AST_Expression_UMinus uminusExp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visitClassWrapper(AST_Element_ClassWrapper){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

}
