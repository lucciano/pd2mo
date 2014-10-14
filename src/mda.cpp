#include <traverser.h>
#include <mda.h>
#include <string>

namespace pd2mo{

AST_Declaration mda::visitDeclaration(AST_Declaration dec){
	return Traverser::visitDeclaration(dec);
}

AST_Expression_ComponentReference 
	mda::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	return Traverser::visitExpression_ComponentReference(compRefExp);
}

AST_DeclarationList mda::visitDeclarationList(AST_DeclarationList decList){
	AST_DeclarationListIterator it;
	AST_DeclarationList ret = new list<AST_Declaration>();
	foreach(it, decList){
		AST_Declaration dec = visitDeclaration(current_element(it));
		AST_ExpressionList indexes = dec->indexes();
		if(indexes->size() >= 2){
			cout << dec->name() << " un buen candidato para eliminar o remplazar" << endl;
			AST_ExpressionListIterator itExp;

			foreach(itExp, indexes){
				if(current_element(itExp)->expressionType() == EXPINTEGER){
					AST_Expression_Integer itExpInteger = current_element(itExp)->getAsInteger();
					if(itExpInteger->val() == 1){
						cout << dec->name() << "(1) podemos eliminar una dimension " << endl;
						//indexes->erase(itExp);
					}else{
						//indexes->erase(itExp);
						AST_ExpressionList altDec = new std::list<AST_Expression>();
						for(int i = 1; i <= itExpInteger->val(); i++){
							std::stringstream ss;
							std::string label;
							ss << dec->name() << "_"<< i;
							label = ss.str();
							cout << label << " redimensionado" << endl;
							//new AST_Declaration_ (dec->name() + itoa(i), 
							//	visitExpressionList(dec->indexes()),
							//	visitModification(dec->modification()))
							
						}
					}
				}else{
					cout << dec << endl;
				}
			}
		}else{
			if(dec->modification() and dec->modification()->modificationType() == MODEQUAL and
			   dec->modification()->getAsEqual()->exp()->expressionType() == EXPINTEGER){
				var[dec->name()] = dec->modification()->getAsEqual()->exp()->getAsInteger();
			}
			ret->insert(ret->end(), dec);
		}
	}
	return ret;
}

}
