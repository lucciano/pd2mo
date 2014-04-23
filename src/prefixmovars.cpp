#include <prefixmovars.h>
#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{
AST_Class PrefixMoVars::visitClass(AST_Class _class){
	debug << __PRETTY_FUNCTION__ << _class->name() << endl  ; 
	return Traverser::visitClass(_class);
}

AST_Declaration PrefixMoVars::visitDeclaration(AST_Declaration dec){
	debug << __PRETTY_FUNCTION__ << dec->name() << endl  ; 
	AST_ExpressionListIterator it;
	foreach(it, dec->indexes()){
		cout <<"Indices " << current_element(it) << endl;
	}
	return Traverser::visitDeclaration(dec);
}
AST_Modification_Equal PrefixMoVars::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << modEq << endl  ; 
	Traverser::visitExpression(modEq->exp());
	return visitModification_Equal(modEq);
}
}
