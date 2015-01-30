#include <src/range.h>
#include <util/symbol_table.h>

namespace pd2mo{

AST_Expression range::visitExpression(AST_Expression exp){
	if(exp->expressionType() != EXPCOMPREF){
		return Traverser::visitExpression(exp);
	}
	
	AST_Expression_ComponentReference comp = exp->getAsComponentReference();
	
	AST_ExpressionListListIterator it;
	AST_ExpressionListList expList = comp->indexes();
	bool doExpand = false;
	int i = 0;
	AST_Expression v_exp1;
	AST_Expression v_exp2;

	AST_StringListIterator names = comp->names()->begin();
	foreach(it, expList){
		AST_ExpressionList argList = new std::list<AST_Expression>();
		AST_String name = *names;
		names ++;
		int j = 0;
		AST_ExpressionListIterator itExp;
		AST_ExpressionList expList = current_element(it);
		foreach(itExp, expList){
			if(current_element(itExp)->expressionType() == EXPRANGE){
				cout << name << "exp pos: " << i << ", " << j;
				AST_Expression_Range expRange = current_element(itExp)->getAsRange();
				AST_Expression exp1 = *(expRange->expressionList()->begin());
				AST_Expression exp2 = *(std::next(expRange->expressionList()->begin(),1));
				EvalExp *evalExp = new EvalExp(_c_class->getVarSymbolTable());
				v_exp1 = evalExp->eval(evalExp->eval(visitExpression(exp1)));
				v_exp2 = evalExp->eval(evalExp->eval(visitExpression(exp2)));
				if(v_exp1->expressionType() == EXPINTEGER and v_exp1->expressionType() == EXPINTEGER){
					for(int k = v_exp1->getAsInteger()->val() ; k <= v_exp2->getAsInteger()->val(); k++){
						
						AST_ExpressionList intList = new std::list<AST_Expression>();
						if(j>0){
							intList->insert(intList->end(), 
								expList->begin(), 
								std::next(expList->begin(), j)); 
						}
						intList->insert(intList->end(), new AST_Expression_Integer_(k));
						if(j<expRange->expressionList()->size()){
							intList->insert(intList->end(), 
								std::next(expList->begin(), j+1),
								expList->end());
						}
						AST_Expression_ComponentReference newExp = new AST_Expression_ComponentReference_();
						newExp->append(name, intList);
						argList->insert(argList->end(), newExp);
					}
					doExpand = true;
					break;
				}
			}
			cout << endl;
			j++;
		}
		i++;
		if(doExpand) {
			AST_Expression altComp = new AST_Expression_Brace_(argList);
			exp = visitExpression(altComp);
			break;
		}else{
			delete argList;
		}
	}
	return exp;
};

AST_Class range::visitClass(AST_Class _class){
        TypeSymbolTable tyEnv = newTypeSymbolTable();
        _c_class = newMMO_Class(_class, tyEnv);
        AST_Class rtr = Traverser::visitClass(_class);
        delete _c_class;
        return rtr;
};



}
