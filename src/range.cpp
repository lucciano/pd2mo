#include <src/range.h>

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
				cout << exp1 << "-->" << exp2 << endl;
			}
		}
	}
	return comp;
};


}
