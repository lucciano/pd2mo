#include <setParameters.h>

Time tf = 0;

namespace pd2mo{
void SetParameters::setParametersList(QStringList x){ 
	QStringList::iterator it;
	exp = new list<AST_Expression>;
	for(it = x.begin(); it != x.end(); it++){
		char * d_str = (char*) malloc(sizeof(char) * it->toStdString().size());
		strcpy (d_str,  it->toStdString().c_str());
		double d = getScilabVar(d_str);
		free(d_str);
		AST_Expression_Real ra = new AST_Expression_Real_(d);
		exp->insert(exp->end(), ra);
	}
}
AST_Declaration SetParameters::visitDeclaration(AST_Declaration dec){
	string name = dec->name();
	debug_out << __PRETTY_FUNCTION__ << name << endl  ; 

	AST_Declaration decPrefix;
	if(this->paramsName.compare(name) == 0){
		debug_out << "Found param : " << name << endl;
		//dec->modification()->getAsEqual()->exp() << endl;
		AST_Expression_Brace braces = new AST_Expression_Brace_ (exp);
		AST_Modification_Equal mo = new AST_Modification_Equal_(braces);
		decPrefix = new AST_Declaration_(name, 
			this->visitExpressionList(dec->indexes()), mo);

	}else{
		decPrefix = new AST_Declaration_(name, 
			this->visitExpressionList(dec->indexes()),
			this->visitModification(dec->modification()));
	}
	decPrefix->setComment(dec->comment());
	return decPrefix;

	
}

AST_Expression_ComponentReference SetParameters::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
        debug_out << __PRETTY_FUNCTION__ << compRefExp->name() << endl  ;
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
