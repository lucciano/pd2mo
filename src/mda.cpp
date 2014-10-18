#include <traverser.h>
#include <mda.h>
#include <string>

//TODO : expandir el for ... :(

namespace pd2mo{


AST_Declaration mda::visitDeclaration(AST_Declaration dec){
	return Traverser::visitDeclaration(dec);
}



//TODO: a level up (the calling function) will look better in the code
AST_DeclarationList mda::visitDeclarationList(AST_DeclarationList decList){
	AST_DeclarationListIterator it;
	AST_DeclarationList ret = new list<AST_Declaration>();
	foreach(it, decList){
		AST_Declaration dec = visitDeclaration(current_element(it));
		AST_ExpressionList indexes = dec->indexes();
		if(indexes->size() >= 2){
			//cout << dec->name() << " un buen candidato para eliminar o remplazar" << endl;
			AST_ExpressionListIterator itExp;

			foreach(itExp, indexes){
				//TODO, podemos procesar si es una referenceExpresion y la tenemos en var
				if(current_element(itExp)->expressionType() == EXPINTEGER and 
					current_element(itExp)->getAsInteger()->val() == 1)
				{
					//cout << dec->name() << "(1) podemos eliminar una dimension " << endl;
						//indexes->erase(itExp);
				}else{
					if(current_element(itExp)->expressionType() == EXPCOMPREF and
				        var.find(current_element(itExp)
						->getAsComponentReference()
						->name()) != var.end() and
					   itExp != indexes->begin()
					  )
					{
						int x = var[current_element(itExp)
							->getAsComponentReference()
							->name()]->val();
						for(int i  = 1; i <= x; i++){
							AST_ExpressionList altInx = new std::list<AST_Expression>();
							altInx->insert(altInx->begin(),
									std::next(itExp,0),  
									indexes->end());
							std::stringstream ss;
							ss << dec->name() << "_" << i;
							AST_Declaration dec2 = new AST_Declaration_(ss.str(),
										altInx, dec->modification());
				
							ret->insert(ret->end(), dec2);
						}
						//cout << x << endl;
					}
				}
			}
		}else{
			if(dec->modification() and dec->modification()->modificationType() == MODEQUAL and
			   dec->modification()->getAsEqual()->exp()->expressionType() == EXPINTEGER){
				var[dec->name()] = dec->modification()->getAsEqual()->exp()->getAsInteger();
				//cout << dec->name() << "=" <<  var[dec->name()] << endl;
			}
			ret->insert(ret->end(), dec);
		}
	}
	return ret;
}

AST_Expression mda::lookUpVar (AST_Expression exp){
	if(exp->expressionType() == EXPCOMPREF and 
		var.find(exp->getAsComponentReference()->name()) != var.end()){
		return lookUpVar(var[exp->getAsComponentReference()->name()]);
	}else{
		return exp;
	}
}

AST_EquationList mda::visitEquationList(AST_EquationList eqList){
	AST_EquationListIterator it;
	AST_EquationList ret = new list<AST_Equation>();
	foreach(it, eqList){
		if(current_element(it)->equationType() == EQFOR){
			AST_Equation_For eqFor = current_element(it)->getAsFor();
			AST_ForIndexList eqForIndexList = eqFor->forIndexList();
			AST_ForIndexListIterator itf;
			foreach(itf, eqForIndexList){
				AST_ForIndex indexFor = current_element(itf);
				//TODO : check that the for can be exanded (i.e. it goes from IntExp to IntExp)
				if (indexFor->in_exp()->expressionType() == EXPRANGE){
					AST_ExpressionList expList = indexFor->in_exp()->getAsRange()->expressionList();
					if(expList->size() == 2){
						AST_Expression from, to;
						from = *(expList->begin());
						to = *(++expList->begin());
						if (lookUpVar(from)->expressionType() == EXPINTEGER and
							lookUpVar(to)->expressionType() == EXPINTEGER ){
							for(int i = lookUpVar(from)->getAsInteger()->val();
							   i <= lookUpVar(to)->getAsInteger()->val();
							   i++){//TODO chequear que los forms son siempre de a uno.
								std::string variable = * (indexFor->variable());
								var[variable] = new AST_Expression_Integer_(i);
								AST_EquationList fEqList = visitEquationList(eqFor->equationList());
								ret->insert(ret->end(), fEqList->begin(), fEqList->end());
							//TODO . Add the var to the prefix stack
							}
						}else{
							ret->insert(ret->end(), visitEquation(current_element(it)));
						}
					}
				}else{
					ret->insert(ret->end(), visitEquation(current_element(it)));
				}
			}
		}else{
			//cout <<visitEquation(current_element(it)) << endl;
			ret->insert(ret->end(), visitEquation(current_element(it)));
		}
	}
	return ret;
}

AST_Expression_ComponentReference 
	mda::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){

	//TODO : Check if we have an element on the stack, if we do we may be able to rewrite the reference and drop an index.
	if(compRefExp->indexes()->size() > 0 and (*compRefExp->indexes()->begin())->size() > 1){
		cout << compRefExp << endl;
		AST_ExpressionListIterator it;

		std::stringstream ss;
		cout << "name:" << *(compRefExp->names()->begin()) << endl;
		ss <<*(compRefExp->names()->begin());
		bool first = true;
		AST_ExpressionList expList = new std::list<AST_Expression>();
		foreach(it, (*compRefExp->indexes()->begin())){
			if(!first and lookUpVar(current_element(it))->expressionType() == EXPINTEGER){//TODO: keep track, if we remove the index (==1) or not
				ss << "_" <<lookUpVar(current_element(it));
			}else{
				expList->insert(expList->end(), lookUpVar(current_element(it)));
			}
			first = false;
		}
		AST_Expression_ComponentReference newref = new AST_Expression_ComponentReference_ ();
		std::string * varname = new std::string(ss.str());
		newref->append(varname, expList);
		return newref;
	}else{
		return Traverser::visitExpression_ComponentReference(compRefExp);
	}
}

AST_Statement_For mda::visitStatement_For(AST_Statement_For stFor){
//	cout << "------------------stFor-----------------"<< endl;
//	cout << stFor << endl;
//	cout << "------------------stFor-----------------"<< endl;
	return Traverser::visitStatement_For(stFor);
}

AST_Expression mda::visitExpression(AST_Expression ex){
	return lookUpVar(Traverser::visitExpression(ex));
}

}
