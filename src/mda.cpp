#include <traverser.h>
#include <mda.h>
#include <string>

namespace pd2mo{

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
					AST_ExpressionListIterator a1_it= std::next(indexes->begin(),1);
					AST_Expression a1 = lookUpVar(*a1_it);
					if(a1->expressionType() == EXPINTEGER){
						
						skyp_element = true;
						AST_DeclarationList decList = new std::list<AST_Declaration>();
						for(int i = 1; i <= a1->getAsInteger()->val(); i++){
							
							std::stringstream ss;
							ss <<(comp->name());
							ss << "_" << i;
							AST_ExpressionListIterator indexIt;
							AST_ExpressionList ss_list = new std::list<AST_Expression>();
							foreach(indexIt, indexes){
								if(indexIt == a1_it){
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


AST_Expression_ComponentReference 
	mda::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	if(compRefExp->indexes()->size() > 0 and (*compRefExp->indexes()->begin())->size() > 1){
		AST_ExpressionListIterator it;
		std::stringstream ss;
		ss <<*(compRefExp->names()->begin());
		bool first = true;
		AST_ExpressionList expList = new std::list<AST_Expression>();
		foreach(it, (*compRefExp->indexes()->begin())){
			if(!first and lookUpVar(current_element(it))->expressionType() == EXPINTEGER){
				ss << "_" <<lookUpVar(current_element(it));
			}else{
				expList->insert(expList->end(), visitExpression(lookUpVar(current_element(it))));
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

AST_Expression mda::visitExpression(AST_Expression ex){
	if(ex != NULL) return lookUpVar(Traverser::visitExpression(ex));
	else return NULL;
}

}
