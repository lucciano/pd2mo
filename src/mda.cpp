#include <traverser.h>
#include <mda.h>
#include <string>

namespace pd2mo{

AST_DeclarationList mda::visitDeclarationList(AST_DeclarationList decList){
	AST_DeclarationListIterator it;
	AST_DeclarationList ret = new list<AST_Declaration>();
	foreach(it, decList){
		AST_Declaration dec = visitDeclaration(current_element(it));
		if(dec->modification() and dec->modification()->modificationType() == MODEQUAL
			and lookUpVar(dec->modification()->getAsEqual()->exp())->expressionType() == EXPINTEGER 
		){
			var[dec->name()] = lookUpVar(dec->modification()->getAsEqual()->exp())->getAsInteger();
			//cout << dec->name() << "@ line : " <<__LINE__ << dec->modification()->getAsEqual()->exp() << endl;
		}
		ret->insert(ret->end(), visitDeclaration(dec));
	}
	return ret;
}

AST_Expression mda::lookUpVar (AST_Expression exp){
	if(exp->expressionType() == EXPCOMPREF and 
		var.find(exp->getAsComponentReference()->name()) != var.end() and 
		var[exp->getAsComponentReference()->name()] != NULL){
		return lookUpVar(var[exp->getAsComponentReference()->name()]);
	}else if(exp->expressionType() == EXPBINOP and 
		exp->getAsBinOp()->binopType() == BINOPADD and
		lookUpVar(exp->getAsBinOp()->left())->expressionType() == EXPINTEGER and
		lookUpVar(exp->getAsBinOp()->right())->expressionType() == EXPINTEGER){
		AST_Integer expInt = lookUpVar(exp->getAsBinOp()->left())->getAsInteger()->val() +
				lookUpVar(exp->getAsBinOp()->right())->getAsInteger()->val();
		return new AST_Expression_Integer_(expInt);
	}else{
		if(exp->expressionType() == EXPCOMPREF and var.find(exp->getAsComponentReference()->name()) != var.end()){
			//cout << "no found @ var " << exp->getAsComponentReference()->name() << (NULL == var[exp->getAsComponentReference()->name()]) << endl;
		}
		return exp;
	}
}

AST_ElementList mda::visitElementList(AST_ElementList elementList){
	AST_ElementListIterator itelemen;
	AST_ElementList ret = new list<AST_Element>(); 
	foreach(itelemen, elementList){
		bool skyp_element = false;
		if(current_element(itelemen)->elementType() == COMPONENT){
			AST_Element_Component comp = current_element(itelemen)->getAsComponent();

			AST_DeclarationListIterator it;
			foreach(it, comp->nameList()){
				AST_Declaration dec = current_element(it);
				AST_ExpressionList indexes = dec->indexes();
				if(indexes->size() >= 2){
					AST_Expression a1 = lookUpVar(*indexes->begin());
					//AST_Expression a2 = lookUpVar(*std::next(indexes->begin(),1));
					if(a1->expressionType() == EXPINTEGER){
						//cout << comp->name() << "[" <<a1 <<"]" << endl;
						
						skyp_element = true;
						AST_DeclarationList decList = new std::list<AST_Declaration>();
						for(int i = 1; i <= a1->getAsInteger()->val(); i++){
							std::stringstream ss;
							ss <<(comp->name());
							ss << "_" << i;
							AST_ExpressionListIterator indexIt;
							AST_ExpressionList ss_list = new std::list<AST_Expression>();
							foreach(indexIt, indexes){
								if(indexIt == indexes->begin()){
									continue;
								}
								ss_list->insert(ss_list->end(), visitExpression(current_element(indexIt)));
							}

							AST_DeclarationList expList = new std::list<AST_Declaration>();
							AST_Declaration newDec = new AST_Declaration_(ss.str(), ss_list, 
											visitModification(dec->modification()));
							decList->insert(decList->end(), newDec);
						}
						declr[comp->name()] = decList;

						ret->insert(ret->end(), new AST_Element_Component_ ( decList, comp->type(), 
							comp->typePrefix(), visitExpressionList(comp->indexes())));

					}
				}else{
					if(dec->modification() and dec->modification()->modificationType() == MODEQUAL and
					   lookUpVar(dec->modification()->getAsEqual()->exp())->expressionType() == EXPINTEGER){
						var[dec->name()] = lookUpVar(dec->modification()->getAsEqual()->exp())->getAsInteger();
						//cout << "var <- " << dec->name() << " <- " << var[dec->name()] << endl;
					}
				}
				
			}
			
		}
		if(!skyp_element){
			ret->insert(ret->end(), visitElement(current_element(itelemen)));
		}	

        }

	return ret;
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
								//cout << "borrando :" << variable << endl;
								var.erase(variable);
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
	if(compRefExp->indexes()->size() > 0 and (*compRefExp->indexes()->begin())->size() > 1){
		AST_ExpressionListIterator it;

		std::stringstream ss;
		//cout << "name:" << *(compRefExp->names()->begin()) << endl;
		ss <<*(compRefExp->names()->begin());
		bool first = true;
		AST_ExpressionList expList = new std::list<AST_Expression>();
		foreach(it, (*compRefExp->indexes()->begin())){
			if(first and lookUpVar(current_element(it))->expressionType() == EXPINTEGER){//TODO: keep track, if we remove the index (==1) or not
				ss << "_" <<lookUpVar(current_element(it));
			}else{
				//cout << compRefExp << "- -- - " << current_element(it) << "=" << lookUpVar(current_element(it)) ;
				expList->insert(expList->end(), visitExpression(lookUpVar(current_element(it))));
			}
			first = false;
		}
		AST_Expression_ComponentReference newref = new AST_Expression_ComponentReference_ ();
		std::string * varname = new std::string(ss.str());
		newref->append(varname, expList);
		return newref;
	}else{
		//if(declr.find(**(compRefExp->names()->begin())) != declr.end()){
		//	cout <<  "fuckit " << *(compRefExp->names()->begin()) << endl;;
		//}
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
	if(ex != NULL) return lookUpVar(Traverser::visitExpression(ex));
	else return NULL;
}

}
