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

AST_Expression evalp::visitExpression_ComponentReferenceALT(AST_Expression_ComponentReference compRefExp){

        AST_StringListIterator it;
        AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();

	string * name = current_element(compRefExp->names()->begin());
	AST_ExpressionListList indexes = compRefExp->indexes();
	if(compRefExp->names()->size() == 1){	
		if(name->compare("p") == 0){
		//	AST_ExpressionListListIterator itIndex = indexes->begin();
			if(indexes->size() == 1 and current_element(indexes->begin())->size() == 1){
				AST_Expression index = current_element(current_element(indexes->begin())->begin());
				//cout << index->expressionType() << index->getAsInteger() << endl;
				return new AST_Expression_Integer_(22);
			}
		}
	}
	AST_Expression_ComponentReference rVal =
		new AST_Expression_ComponentReference_ ();

	rVal->append(name,
		visitExpressionList(current_element(indexes->begin())));

	return rVal;
}

AST_Expression evalp::visitExpression(AST_Expression ex){
        switch(ex->expressionType()){
        case EXPCOMPREF:
                //debug << "EXPCOMPREF:" << endl;
                return visitExpression_ComponentReferenceALT(ex->getAsComponentReference());
	}
	return Traverser::visitExpression(ex);
}

AST_String evalp::visitVariable(AST_String s){
	return s;
}

}
