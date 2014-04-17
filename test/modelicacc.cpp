#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <test/file_util.h>
#include <string>
#include <ast/stored_definition.h>
#include <ast/modification.h>
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
	cout << "AST_ElementList" << endl;
	foreach(elit,el) {
		AST_Element el = current_element(elit);
		AST_Element_Component elco;
		AST_DeclarationList decl; 
		AST_DeclarationListIterator declit;
		AST_ExpressionList expl;
		cout << el <<endl;
		switch(el->elementType()){
			case ELNONE:
				cout << "Type ELNONE" <<endl; break;
			case COMPONENT:
				{
				cout << "Type COMPONENT" <<endl; 
				elco = el->getAsComponent();
				cout << "Variable :"<< elco->name() << endl; 
				AST_DeclarationList  decl = elco->nameList ();
				AST_DeclarationListIterator it;
				foreach(it, decl){
					cout <<"Var:" << current_element(it)->name() << endl;
				}
				AST_Modification m;
				decl = elco->nameList();
				foreach(declit, decl){
					if(current_element(declit)->modification()){
					m = current_element(declit)->modification();
					cout << m->modificationType() << endl;
					cout << current_element(declit)->name() << "<<==" 
					     << current_element(declit)->modification() << endl;
					}else{
						cout << current_element(declit)->name() << "<<==" << endl;
					}
				}
				AST_ExpressionList   expl = elco->indexes ();
				cout << "Index :" << expl->size() << endl;
				AST_ExpressionListIterator explit;
				foreach(explit, expl){
					cout << "Exp:" << current_element(it) << endl;
				}
				cout << "......................................\n";
				}
				break;
			case IMPORT:
				cout << "Type IMPORT" <<endl; break;
			case EXTENDS:
				cout << "Type EXTENDS" <<endl; break;
			case ELCLASS:
				cout << "Type ELCLASS" <<endl; break;
			default:
				cout << "Type UNKOWN" <<endl; break;
		}
                //        
                //        AST_ExpressionList dims = newAST_ExpressionList();
                //        AST_ListConcat(dims, current_element(it)->indexes() );
                //        AST_ListConcat(dims, c->indexes() );
                //        
                //        if (dims->size() > 0 )
                //                t = make_array_type(  dims, t  );
                //        
                //        VarInfo  v = newVarInfo(t , c->typePrefix() , current_element(it)->modification(), current_element(it)->comment() );
                //        varEnv->insert(current_element(it)->name(), v);
                ////}

	}
	
	
	AST_CompositionElementList cel = comp->compositionList();
	AST_CompositionElementListIterator it;
	cout << "CompositionElements" <<endl;
	foreach(it,cel) {
		AST_EquationListIterator eqit;
		AST_ElementListIterator  elit;
		AST_StatementListIterator stit;
		
		// Equations 
		AST_CompositionElement e = current_element(it);
		AST_CompositionEqsAlgs eqA = e->getEquationsAlgs();
		if (eqA != NULL) {
				cout << "Equations"<< endl;
				foreach(eqit,eqA->getEquations())  
					cout << current_element(eqit) << endl;
				foreach(stit,eqA->getAlgorithms()) 
					cout << current_element(stit) << endl;
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
