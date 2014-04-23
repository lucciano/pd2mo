#include <prefixmovars.h>
#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
void PrefixMoVars::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << _class->name() << endl  ; 
	Traverser::visitClass(_class);
}

void PrefixMoVars::visitDeclaration(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << dec->name() << endl  ; 
	AST_ExpressionListIterator it;
	foreach(it, dec->indexes()){
		cout <<"Indices " << current_element(it) << endl;
	}
	Traverser::visitDeclaration(dec);
}
void PrefixMoVars::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << modEq << endl  ; 
	Traverser::visitExpression(modEq->exp());
}
}
