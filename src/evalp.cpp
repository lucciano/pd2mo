#include <evalp.h>

namespace pd2mo {
AST_Declaration evalp::visitDeclaration(AST_Declaration dec){
        string name = dec->name();
        AST_Declaration decPrefix = new AST_Declaration_(name,
                this->visitExpressionList(dec->indexes()),
                this->visitModification(dec->modification()));
        decPrefix->setComment(dec->comment());
        dec = decPrefix;
        return decPrefix;
}

AST_Expression_ComponentReference evalp::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
        AST_Expression_ComponentReference rVal =
                 new AST_Expression_ComponentReference_ ();

        AST_StringListIterator it;
        AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
        foreach (it, compRefExp->names()) {
                string * name = new string(*current_element(it));
		cout << "->"<< name << "(" ;
		AST_ExpressionListIterator exp_it_it = current_element(exp_it)->begin();
		foreach(exp_it_it, current_element(exp_it)){
			cout << current_element(exp_it_it) << " ";
		}
		cout << ")" <<endl;
                rVal->append(name,
                        visitExpressionList(current_element(exp_it)));
                exp_it++;
        }
        return rVal;
}

AST_String evalp::visitVariable(AST_String s){
	return s;
}

}
