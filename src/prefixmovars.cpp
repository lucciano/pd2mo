#include <prefixmovars.h>
#include <traverser.h>
#include <iostream>
#define debug std::cout 

namespace pd2mo{

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

AST_Expression_ComponentReference PrefixMoVars::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
        debug << __PRETTY_FUNCTION__ << compRefExp->name() << endl  ;
        AST_Expression_ComponentReference rVal =
                 new AST_Expression_ComponentReference_ ();

        AST_StringListIterator it;
        AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
        foreach (it, compRefExp->names()) {
		string * name = new string(this->prefix + *current_element(it));
                rVal->append(name,
                        visitExpressionList(current_element(exp_it)));
                exp_it++;
        }
        return rVal;
}

}
