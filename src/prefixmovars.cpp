#include <prefixmovars.h>
#include <traverser.h>

namespace pd2mo{

AST_Declaration PrefixMoVars::visitDeclaration(AST_Declaration dec){
	string name = this->prefix + dec->name();
	AST_Declaration decPrefix = new AST_Declaration_(name, 
		this->visitExpressionList(dec->indexes()),
		this->visitModification(dec->modification()));
	decPrefix->setComment(dec->comment());
	dec = decPrefix;
	return decPrefix;
}

AST_Expression_ComponentReference PrefixMoVars::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
        AST_Expression_ComponentReference rVal =
                 new AST_Expression_ComponentReference_ ();

        AST_StringListIterator it;
        AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
        foreach (it, compRefExp->names()) {
		string * name;
		if(current_element(it)->compare("time") == 0){
			name = new string(*current_element(it));
		}else{
			name = new string(this->prefix + *current_element(it));
		}
                rVal->append(name,
                        visitExpressionList(current_element(exp_it)));
                exp_it++;
        }
        return rVal;
}

AST_String PrefixMoVars::visitVariable(AST_String s){
	string * rtr ;
	if(s->compare("time") == 0){
		rtr = new string(*s);
	}else{
		rtr = new string(prefix + (*s));
	}
	return rtr;
}

}
