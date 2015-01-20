#include <if.h>
#include <util/symbol_table.h>
using namespace pd2mo;
AST_EquationList If::visitEquationList (AST_EquationList eqList){
	//debug << __PRETTY_FUNCTION__ << endl ;
	AST_EquationListIterator it;
	AST_EquationList ret = new list<AST_Equation>();
	foreach(it, eqList){
		AST_Equation eq = current_element(it);
		switch (eq->equationType()){

		case EQIF:{
			AST_Equation_If eqIf = eq->getAsIf();
			cout << eqIf->condition() << ".-.-.-.-" << endl;
			cout << _c_class << ".-.-.-.-" << endl;
			EvalExp *evalExp = new EvalExp(_c_class->getVarSymbolTable());
			AST_Expression exp = evalExp->eval(eqIf->condition());
			if(exp->expressionType() == EXPBOOLEAN){
				if(exp->getAsBoolean()->value()){
					AST_EquationList eqList2 = visitEquationList(eqIf->equationList());
					ret->insert(ret->end(), eqList2->begin(), eqList2->end());
				}else{
					bool foundCond = false;
					// TODO : handle stIf ->else_if()
					AST_Equation_ElseList eq_elseList = eqIf->equationElseIf(); 
					AST_Equation_ElseListIterator it_else;
					foreach(it_else, eq_elseList){
						AST_Equation_Else exp_else = current_element(it_else);
						AST_Expression exp_p = evalExp->eval(exp_else->condition());
						if(exp_p->expressionType() == EXPBOOLEAN and 
							exp_p->getAsBoolean()->value()){
							foundCond = true;
							AST_EquationList eqList2 = visitEquationList(exp_else->equations());
							ret->insert(ret->end(), eqList2->begin(), eqList2->end());
						}
					}
					if(!foundCond){
						AST_EquationList eqList2 = visitEquationList(eqIf->equationElseList());
						ret->insert(ret->end(), eqList2->begin(), eqList2->end());
					}

				}
				break;
			}
		}
		default:
			ret->insert(ret->end(), Traverser::visitEquation(eq));
		}
	}
	return ret;
}

AST_Class If::visitClass(AST_Class _class){

	TypeSymbolTable tyEnv = newTypeSymbolTable();
	_c_class = newMMO_Class(_class, tyEnv);
	AST_Class rtr = Traverser::visitClass(_class);
	delete _c_class;
	return rtr;
}
