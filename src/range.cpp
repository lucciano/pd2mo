#include <src/range.h>
#include <util/symbol_table.h>

namespace pd2mo{

AST_Expression_ComponentReference range::visitExpression_ComponentReference(AST_Expression_ComponentReference comp){
	std::cout <<"-.-.-.-.-.-.-.-.-.-.-.-." << comp->name() <<
	
		".-.-.-.-.-.-.-.-.-.-.-.-.-."<< std::endl;
	AST_ExpressionListListIterator it;
	AST_ExpressionListList expList = comp->indexes();
	foreach(it, expList){

		AST_ExpressionListIterator itExp;
		AST_ExpressionList exp = current_element(it);
		foreach(itExp, exp){
			if(current_element(itExp)->expressionType() == EXPRANGE){
				AST_Expression_Range expRange = current_element(itExp)->getAsRange();
				AST_Expression exp1 = *(expRange->expressionList()->begin());
				AST_Expression exp2 = *(std::next(expRange->expressionList()->begin(),1));
				EvalExp *evalExp = new EvalExp(_c_class->getVarSymbolTable());
				AST_Expression v_exp1 = evalExp->eval(evalExp->eval(exp1));
				AST_Expression v_exp2 = evalExp->eval(evalExp->eval(exp2));
				cout << v_exp1 << "-->" << v_exp2 << endl;

			}
		}
	}
	return comp;
};

AST_Class range::visitClass(AST_Class _class){
        TypeSymbolTable tyEnv = newTypeSymbolTable();
        _c_class = newMMO_Class(_class, tyEnv);
        AST_Class rtr = Traverser::visitClass(_class);
        delete _c_class;
        return rtr;
};



}
