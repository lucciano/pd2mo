#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <string>
#include <ast/stored_definition.h>
#include <parser/parse.h>
#include <util/symbol_table.h>
#include <util/ast_util.h>

using namespace std;

BOOST_AUTO_TEST_CASE( cero ) {
    BOOST_CHECK( 1 == 1 );
    int r = 0;
    string path = getFullPath();
    string filename = path + "/data/Constant.mo";
    cout << filename << endl;
    AST_StoredDefinition sd = parseFile(filename,&r);
    AST_ClassList models = sd->models();
    AST_ClassListIterator mIter;
    for(mIter = models->begin(); mIter != models->end(); ++mIter){
	AST_Class c = (*mIter);
	BOOST_CHECK( 0 == c->name()->compare("Constant"));

	cout << "Encontramos la clase " << c->name() << endl;
	for( AST_ElementListIterator cIter = c->composition()->elementList()->begin();
		cIter != c->composition()->elementList()->end(); ++cIter){
		//cout << (*cIter) << endl;
	}
	AST_CompositionElementList cl = c->composition()->compositionList();
	AST_CompositionElementListIterator it;
	foreach(it, cl){
		AST_EquationList eql = (*it)->getEquationsAlgs()->getEquations();
		AST_EquationListIterator it2;
		foreach(it2, eql){
			cout << (*it2) << endl;
		}
	}
    }
}

BOOST_AUTO_TEST_CASE( uno) {
    string path = getFullPath();
    string filename = path + "/data/Model01.mo";

    int r = 0;
    AST_StoredDefinition sd = parseFile(filename,&r);
    
    cout << filename << endl;

    AST_ClassList models = sd->models();
    AST_ClassListIterator mIter;
    for(mIter = models->begin(); mIter != models->end(); ++mIter){
	AST_Class c = (*mIter);
	
	AST_Composition comp = c->composition();

	// First elements
	AST_ElementList el = comp->elementList();
	AST_ElementListIterator elit;
	foreach(elit,el) {
		//switch (current_element(elit)->elementType()) {
		//	case COMPONENT:
		//		addVariable(current_element(elit)->getAsComponent());
		//		break;
		//	default:
		//		addElement(current_element(elit));
		//		break;
		//}
	}
	
	
	AST_CompositionElementList cel = comp->compositionList();
	AST_CompositionElementListIterator it;
	
	foreach(it,cel) {
		AST_EquationListIterator eqit;
		AST_ElementListIterator  elit;
		AST_StatementListIterator stit;
		
		// Equations 
		AST_CompositionElement e = current_element(it);
		AST_CompositionEqsAlgs eqA = e->getEquationsAlgs();
		if (eqA != NULL) {
			if  (eqA->isInitial()) {
				foreach(eqit,eqA->getEquations())  
					cout << current_element(eqit) << endl;
				foreach(stit,eqA->getAlgorithms()) 
					cout << current_element(stit) << endl;
			} else {
				foreach(eqit,eqA->getEquations())  
					cout << current_element(eqit) << endl;
				foreach(stit,eqA->getAlgorithms()) 
					cout << current_element(stit) << endl;
			}
		}
		// Elements 
		foreach(elit,e->getElementList()) {
			//AST_ListAppend(_comps , current_element(elit)->getAsComponent() );
			cout << current_element(elit)->getAsComponent() << endl;
		}
	}	
	//_ct = new TypeCheck_( tyEnv , varEnv );
	}
}
