#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <setParameters.h>
#include <string>

namespace pd2mo{
AST_Declaration SetParameters::visitDeclaration(AST_Declaration dec){
	string name = dec->name();
	debug << (name == paramsName) << endl;
	debug << __PRETTY_FUNCTION__ << name << endl  ; 
	AST_Declaration decPrefix = new AST_Declaration_(name, 
		this->visitExpressionList(dec->indexes()),
		this->visitModification(dec->modification()));
	decPrefix->setComment(dec->comment());
	dec = decPrefix;
	return decPrefix;

	
}

AST_Expression_ComponentReference SetParameters::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
        debug << __PRETTY_FUNCTION__ << compRefExp->name() << endl  ;
        AST_Expression_ComponentReference rVal =
                 new AST_Expression_ComponentReference_ ();

        AST_StringListIterator it;
        AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
        foreach (it, compRefExp->names()) {
		string * name = new string(*current_element(it));
                rVal->append(name,
                        visitExpressionList(current_element(exp_it)));
                exp_it++;
        }
        return rVal;

}

}
