#include <motools.h>
#include <list>

using namespace std;

MoTool::MoTool(AST_Class c){
	_class = c;
}
AST_ExpressionList MoTool::getDimension(AST_String var){
	AST_ExpressionList rtr = new std::list<AST_Expression_*>();
	AST_ElementList elemList = _class->getAsDefinition()->composition()->elementList();
	bool foundDec = false;
	for( AST_ElementListIterator it = elemList->begin();
		it != elemList->end() && !foundDec; it++){
		//cout << current_element(it) << endl;
		if(current_element(it)->elementType() == COMPONENT){
			AST_DeclarationList decList = current_element(it)->getAsComponent()->nameList();
			for(AST_DeclarationListIterator it2 = decList->begin();
				it2 != decList->end() && !foundDec; it2++){
				AST_Declaration dec = current_element(it2);
				if(dec->name().compare(var->c_str()) == 0){
					//cout << dec->name() << ":" << dec->indexes()->size() << endl;
					rtr->insert(rtr->begin(), dec->indexes()->begin(), dec->indexes()->end());
					foundDec = true;
				}
			}
		}
	}
	
	return rtr;
}
