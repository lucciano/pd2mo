#include <src/prodint.h>
#include <util/symbol_table.h>

namespace pd2mo{

AST_Class prodint::visitClass(AST_Class _class){
        TypeSymbolTable tyEnv = newTypeSymbolTable();
        _c_class = newMMO_Class(_class, tyEnv);
        AST_Class rtr = Traverser::visitClass(_class);
        delete _c_class;
        return rtr;
};



AST_Expression prodint::visitExpression(AST_Expression exp){
	if(exp->expressionType() == EXPBINOP and 
	   exp->getAsBinOp()->binopType() == BINOPMULT
	   ){
		AST_Expression_BinOp expBin = exp->getAsBinOp();
		if( expBin->left()->expressionType() == EXPCOMPREF and
		    expBin->right()->expressionType() == EXPCOMPREF){

			AST_Expression_ComponentReference left = expBin->left()->getAsComponentReference();
			AST_Expression_ComponentReference right = expBin->right()->getAsComponentReference();

			AST_ExpressionList ll = *(left->indexes()->begin()); 
			AST_String nl = *(left->names()->begin());
			AST_ExpressionList lr = *(right->indexes()->begin()); 
			AST_String nr = *(right->names()->begin());

			if(ll->size() == 2 and (*(std::next(ll->begin(),1)))->expressionType() == EXPRANGE and
			   lr->size() == 0){
				
				
				AST_ExpressionListIterator itl;
				
				AST_Expression_Range range = (*(std::next(ll->begin(),1)))->getAsRange();
				EvalExp *evalExp = new EvalExp(_c_class->getVarSymbolTable());

				AST_Expression v_exp1 = evalExp->eval(visitExpression(*range->expressionList()->begin()));
				AST_Expression v_exp2 = evalExp->eval(visitExpression(*std::next(range->expressionList()->begin(),1)));

				if(v_exp1->expressionType() == EXPINTEGER and v_exp2->expressionType() == EXPINTEGER){

					int from = v_exp1->getAsInteger()->val();
					int upto = v_exp2->getAsInteger()->val();
					AST_ExpressionList summan = new std::list<AST_Expression>();
					for(int k = from ; k <= upto; k++){
						AST_Expression_ComponentReference u = new AST_Expression_ComponentReference_();
						AST_ExpressionList ulist = new std::list<AST_Expression>();
						ulist->insert(ulist->end(), visitExpression(*(ll->begin())));
						ulist->insert(ulist->end(), new AST_Expression_Integer_(k));
						u->append(nl, ulist);

						AST_Expression_ComponentReference w = new AST_Expression_ComponentReference_();
						AST_ExpressionList wlist = new std::list<AST_Expression>();
						wlist->insert(wlist->end(), new AST_Expression_Integer_(k));
						w->append(nr,wlist);
						AST_Expression_BinOp mult = new AST_Expression_BinOp_(u,w,BINOPMULT);
						summan->insert(summan->end(), mult);
					}
					AST_ExpressionListIterator it;
					bool first = true;
					AST_Expression prev;
					foreach(it, summan){
						if(first){
							first = false;
							prev = current_element(it);
							continue;
						}
						prev = new AST_Expression_BinOp_(prev, current_element(it), BINOPADD);
					}
					exp = prev;
				}
			}
		}
		
	}
	return Traverser::visitExpression(exp);
};

}
