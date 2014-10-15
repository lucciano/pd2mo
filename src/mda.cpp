#include <traverser.h>
#include <mda.h>
#include <string>

//TODO : expandir el for ... :(

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
				//TODO, podemos procesar si es una referenceExpresion y tenemos la tenemos en var
				if(current_element(itExp)->expressionType() == EXPINTEGER and 
					current_element(itExp)->getAsInteger()->val() == 1)
				{
					cout << dec->name() << "(1) podemos eliminar una dimension " << endl;
						//indexes->erase(itExp);
				}else{
					//TODO : sustituir las dimensiones
						//AST_ExpressionList altDec = new std::list<AST_Expression>();
						//for(int i = 1; i <= itExpInteger->val(); i++){
						//	std::stringstream ss;
						//	std::string label;
						//	ss << dec->name() << "_"<< i;
						//	label = ss.str();
						//	cout << label << " redimensionado" << endl;
						//	//new AST_Declaration_ (dec->name() + itoa(i), 
						//	//	visitExpressionList(dec->indexes()),
						//	//	visitModification(dec->modification()))
						//	
						//}
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

}
