#include <traverser.h>
#include <mda.h>

namespace pd2mo{

AST_Declaration mda::visitDeclaration(AST_Declaration dec){
	if(dec->indexes()->size() > 0){
		def[dec->name()] = dec->indexes();
	}
	AST_ExpressionList simpList = new list< AST_Expression >();
	AST_ExpressionListIterator it; 
	int j = 0;
	AST_Expression prevMult = NULL;
	foreach(it, dec->indexes()){
		j++;
		if (j >= 2) {
			prevMult = new AST_Expression_BinOp_ (prevMult, current_element(it), BINOPMULT);
		}else if (j == 1) {
			prevMult = current_element(it);
		}
	}
	if(prevMult != NULL) simpList->insert(simpList->begin(), prevMult);
	return new AST_Declaration_ (dec->name(),
				visitExpressionList(simpList),
				dec->modification());
}

AST_Expression_ComponentReference mda::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	//cout << compRefExp <<" " << (*compRefExp->indexes()->begin())->size() << endl  ; 
	
        //if (def.count(compRefExp->name())>0)
	//cout << "\t" << compRefExp->name() << def[compRefExp->name()]->size() << endl;
	AST_Expression_ComponentReference rVal =
		 new AST_Expression_ComponentReference_ ();

	AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
	AST_ExpressionListIterator exp_it2;
	AST_StringListIterator it;
	AST_ExpressionListIterator arrRange;
	foreach (it, compRefExp->names()) {
		AST_ExpressionList expList = new list<AST_Expression>();
		if(def.count(*current_element(it))>0
		and current_element(exp_it)->size()) {
		    
		    int size2=current_element(exp_it)->size(),i2=0;
		    AST_ExpressionListIterator itExp = def[(*current_element(it))]->begin();

		    AST_Expression expArr = NULL;
		    foreach (exp_it2,current_element(exp_it)){
			current_element(exp_it2);
			AST_Expression_BinOp mult = new AST_Expression_BinOp_(
						current_element(exp_it2),
						*itExp,BINOPMULT);
			if(expArr){
				expArr = new AST_Expression_BinOp_ (expArr, mult, BINOPADD);
			}else{
				expArr = mult;
			}
			itExp++;
		    }
		    expList->insert(expList->end(), expArr);
                    
		}
		rVal->append(visitString(current_element(it)), visitExpressionList(expList));

		exp_it++;
	}
	return Traverser::visitExpression_ComponentReference(rVal);
}
}
