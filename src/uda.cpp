#include <traverser.h>
#include <uda.h>
#include <string>

//TODO : expandir el for ... :(

namespace pd2mo{

AST_DeclarationList uda::visitDeclarationList(AST_DeclarationList decList){
	return Traverser::visitDeclarationList(decList);
}

AST_ElementList uda::visitElementList(AST_ElementList elementList){
	AST_ElementList ret = new list<AST_Element>(); 
	AST_ElementListIterator it;
	foreach(it, elementList){
		if(current_element(it)->elementType() == COMPONENT){
			AST_Element_Component comp = current_element(it)->getAsComponent();
			AST_DeclarationListIterator itdec;
			AST_DeclarationList decList = new std::list<AST_Declaration>();
			foreach(itdec, comp->nameList()){
				AST_Declaration dec = current_element(itdec);
				AST_ExpressionList explist = dec->indexes();
				AST_ExpressionList altExpList = new std::list<AST_Expression>();
				AST_ExpressionListIterator itexpl;
				int j = 0;
				foreach(itexpl, explist){
					if(current_element(itexpl)->expressionType() == EXPINTEGER and
					   current_element(itexpl)->getAsInteger()->val() == 1){
						//cout << dec->name() << endl;
						var[dec->name()].insert(var[dec->name()].end(),j);
					}else{
						altExpList->insert(altExpList->end(), visitExpression(current_element(itexpl)));
					}
					j++;
				}
				AST_Declaration altDec = new AST_Declaration_(dec->name(), 
										altExpList, 
										visitModification(dec->modification()));
				decList->insert(decList->end(), altDec);
			}
			ret->insert(ret->end(), new AST_Element_Component_ (decList, 
									current_element(it)->getAsComponent()->type(), 
									current_element(it)->getAsComponent()->typePrefix(), 
									current_element(it)->getAsComponent()->indexes())
					);
		}else{
			ret->insert(ret->end(), Traverser::visitElement(current_element(it)));
		}
	}
	return ret;
}

AST_EquationList uda::visitEquationList(AST_EquationList eqList){
	return Traverser::visitEquationList(eqList);
}

AST_Expression_ComponentReference 
	uda::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	string * varname = new string (**(compRefExp->names()->begin()));
	std::map<string, std::list<int>>::const_iterator it = var.find(*varname);
	AST_Expression_ComponentReference rVal =
		 new AST_Expression_ComponentReference_ ();

	if(it!=var.end()){
		AST_ExpressionListIterator it;
		int j = 0;
		std::list<int>::const_iterator iit = var[*varname].begin();
		AST_ExpressionList nplist = new std::list < AST_Expression >();
		foreach(it, (*compRefExp->indexes()->begin())){
			if((*iit) != j){
				nplist->insert(nplist->end(), visitExpression(*it));
			}
			j++;
		}
		rVal->append(varname, nplist);
		//cout << varname << endl;
		return rVal;
	}else{
		return Traverser::visitExpression_ComponentReference(compRefExp);
	}
}

AST_Statement_For uda::visitStatement_For(AST_Statement_For stFor){
//	cout << "------------------stFor-----------------"<< endl;
//	cout << stFor << endl;
//	cout << "------------------stFor-----------------"<< endl;
	return Traverser::visitStatement_For(stFor);
}

AST_Expression uda::visitExpression(AST_Expression ex){
	return Traverser::visitExpression(ex);
}

}
