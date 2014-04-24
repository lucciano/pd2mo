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
	string name = this->prefix + dec->name();
	debug << __PRETTY_FUNCTION__ << name << endl  ; 
	AST_Declaration decPrefix = new AST_Declaration_(name, 
		this->visitExpressionList(dec->indexes()),
		this->visitModification(dec->modification()));
	decPrefix->setComment(dec->comment());
	dec = decPrefix;
	return decPrefix;
}

AST_Modification_Equal PrefixMoVars::visitModification_Equal(AST_Modification_Equal modEq){
	debug << __PRETTY_FUNCTION__ << modEq << endl  ; 
	
	//Traverser::visitExpression(modEq->exp());
	return Traverser::visitModification_Equal(modEq);
}
}
