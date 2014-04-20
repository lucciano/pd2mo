#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
void Traverser::visit(AST_StoredDefinition sd){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassList models = sd->models();
	this->visit(models);

}

void Traverser::visit(AST_ClassList classList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ClassListIterator it;
	foreach(it, classList){
		this->visit(current_element(it));
	}
}

void Traverser::visit(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << endl  ;
	this->visit(_class->composition());

	AST_CompositionElementList compList = _class->composition()->compositionList();
	AST_CompositionElementListIterator compIt;
	foreach(compIt, compList){
		AST_EquationList eql = current_element(compIt)->getEquationsAlgs()->getEquations();
		this->visit(eql);
	}
}

void Traverser::visit(AST_Composition comp){
	debug << __PRETTY_FUNCTION__ << endl ;
	AST_ElementList elList = comp->elementList();
	this->visit(elList);
}

void Traverser::visit(AST_EquationList eqList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_EquationListIterator it;
	foreach(it, eqList){
		switch(current_element(it)->equationType()){
		//  case EQNONE:{
		//}
		  case EQEQUALITY:{
	AST_Equation_Equality eq = current_element(it)->getAsEquality();
	this->visit(eq);
	break;	}
	//	  case EQCONNECT:{
	//AST_Equation_Connect eq = current_element(it)->getAsConnect();
	//this->visit(eq);
	//break;	}
		  case EQCALL:{
	AST_Equation_Call eq = current_element(it)->getAsCall();
	this->visit(eq);
	break;	}
		  case EQFOR:{
	AST_Equation_For eq = current_element(it)->getAsFor();
	this->visit(eq);
	break;	}
		  case EQWHEN:{
	AST_Equation_When eq = current_element(it)->getAsWhen();
	this->visit(eq);
	break;	}
		  case EQIF:{
	AST_Equation_If eq = current_element(it)->getAsIf();
	this->visit(eq);
	break;	}
		  default :
			throw current_element(it)->equationType();
		}
	}
}

void Traverser::visit(AST_Equation_Call eqCall){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Equation_Connect eqCon){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Equation_Equality eqEq){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Equation_For eqFor){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Equation_If eqIf){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Equation_When eqWhen){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_ElementList elementList){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_ElementListIterator elIt;
	foreach(elIt, elementList){
		switch(current_element(elIt)->elementType()){
			this->visit(current_element(elIt));
		case COMPONENT:{
			AST_Element_Component el = current_element(elIt)->getAsComponent();
			this->visit(el);
			break;
		}
		case IMPORT: {
			AST_Element_ImportClause el = current_element(elIt)->getAsImportClause();
			this->visit(el);
			break;
		}
		case EXTENDS: {
			AST_Element_ExtendsClause el = current_element(elIt)->getAsExtendsClause();
			this->visit(el);
			break;
		}
		case ELCLASS: {
			AST_Element_ClassWrapper el = current_element(elIt)->getAsClassWrapper();
			this->visit(el);
			break;
		}
		case ELNONE:
		default:
			throw current_element(elIt)->elementType();
		}
        }

}

void Traverser::visit(AST_Element element){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_ClassWrapper cw){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_Component comp){
	debug << __PRETTY_FUNCTION__ << endl  ;
	AST_DeclarationList  decl = comp->nameList ();
	this->visit(decl);
}

void Traverser::visit(AST_Element_ExtendsClause extends){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_ImportClause import){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_DeclarationList decList){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_DeclarationListIterator it;
	foreach(it, decList){
		this->visit(current_element(it));
	}
}

void Traverser::visit(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	AST_Modification modif = dec->modification();
	if(modif){
		switch(modif->modificationType()){
		case MODEQUAL:{
			AST_Modification_Equal mo = modif->getAsEqual();
			this->visit(mo);
			return ;
		}
		case MODASSIGN:{
			AST_Modification_Assign mo = modif->getAsAssign();
			this->visit(mo);
			return ;
		}
		case MODCLASS:{
			AST_Modification_Class mo = modif->getAsClass();
			this->visit(mo);
			return ;
		}
		case  MODNONE:
		default:
			throw modif->modificationType();
		}
	}
}

void Traverser::visit(AST_Modification mod){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Modification_Assign modASsig){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Modification_Class modClass){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << endl  ; 
	this->visit(modEq->exp());
}

void Traverser::visit(AST_Expression ex){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_BinOp){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Boolean){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_BooleanNot){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Brace){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Call){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_CallArgs){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Colon){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_ComponentReference){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Derivative){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_End){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_If){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_If_ElseIf){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Integer){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Null){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Output){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Range){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_Real){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_String){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Expression_UMinus){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

}
