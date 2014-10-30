#include <traverser.h>
#include <uda.h>
#include <string>

//TODO : expandir el for ... :(

namespace pd2mo{

AST_DeclarationList uda::visitDeclarationList(AST_DeclarationList decList){
	return Traverser::visitDeclarationList(decList);
}

AST_ElementList uda::visitElementList(AST_ElementList elementList){
	return Traverser::visitElementList(elementList);
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
