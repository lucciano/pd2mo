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
}

void Traverser::visit(AST_Composition comp){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_ElementList elementList){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element element){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_ClassWrapper cw){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_Component comp){
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_ExtendsClause extends){ 
	debug << __PRETTY_FUNCTION__ << endl  ;
}

void Traverser::visit(AST_Element_ImportClause import){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_DeclarationList decList){
	debug << __PRETTY_FUNCTION__ << endl  ; 
}

void Traverser::visit(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << endl  ; 
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
