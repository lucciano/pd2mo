#include <evalp.h>

namespace pd2mo {
AST_Declaration evalp::visitDeclaration(AST_Declaration dec){
	return dec;
}

AST_Expression_ComponentReference evalp::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	return compRefExp;
}

AST_String evalp::visitVariable(AST_String s){
	return s;
}

}
