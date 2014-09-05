#include <evalp.h>
#include <simpd/pdevslib.h>

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
				return exp->at(index->getAsInteger()->val()-1);
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
void evalp::setParams(QStringList x){ 
	params = x; 
	QStringList::iterator it;
	exp = new std::vector<AST_Expression>;
	for(it = x.begin(); it != x.end(); it++){
		char * d_str = (char*) malloc(sizeof(char) * it->toStdString().size());
		QString param = *it;
		if(0 == param.mid(0,1).toStdString().compare("\"")){
			param = param.mid(1,param.length()-2);
		}
		strcpy (d_str,  param.toStdString().c_str());
		double d = getScilabVar(d_str);
		free(d_str);
		AST_Expression_Real ra = new AST_Expression_Real_(d);//TODO : check if is INT or REAL
		exp->insert(exp->end(), ra);
	}
}

}
