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
				foreach(itexpl, explist){
					if(current_element(itexpl)->expressionType() == EXPINTEGER and
					   current_element(itexpl)->getAsInteger()->val() == 1){
						cout << dec->name() << endl;
					}else{
						altExpList->insert(altExpList->end(), visitExpression(current_element(itexpl)));
					}
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
	return Traverser::visitExpression_ComponentReference(compRefExp);
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
