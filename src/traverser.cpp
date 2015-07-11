#include <traverser.h>
#include <iostream>

namespace pd2mo{
AST_StoredDefinition Traverser::visitStoredDefinition(AST_StoredDefinition sd){
	return new AST_StoredDefinition_ (visitClassList(sd->models()), 
			       visitString(sd->within()));
}

AST_String Traverser::visitString(AST_String s){
	AST_String ret;
	if(s!= NULL){
	    ret = new string(*s);
	}else{
	    ret = s;
	}
	return ret;
}

AST_ClassList Traverser::visitClassList(AST_ClassList classList){
	AST_ClassListIterator it;
	AST_ClassList retr = new list<AST_Class>();
	foreach(it, classList){
		retr->insert(retr->end(), visitClass(current_element(it)));
	}
	return retr;
}

AST_Class Traverser::visitClass(AST_Class _class){
	AST_Class _retClass = new AST_Class_Definition_ (visitString(_class->getAsDefinition()->name()), 
			visitComposition(_class->getAsDefinition()->composition()));
	_retClass->setPrefixes(_class->prefix());
	return _retClass;
}

AST_Composition Traverser::visitComposition(AST_Composition comp){
	AST_Composition ret = new AST_Composition_ (
			visitElementList(comp->elementList()), 
			visitCompositionElementList(comp->compositionList()));

	if(comp->externalCall() != NULL){
		ret->setExternalFunctionCall(visitExternal_Function_Call(comp->externalCall()));
	}else{
		ret->setExternalFunctionCall(NULL);
	}
	
	return ret;
}

AST_External_Function_Call Traverser::visitExternal_Function_Call(AST_External_Function_Call exFunCall){
	return new AST_External_Function_Call_(visitString(exFunCall->language()),
			visitArgumentList(exFunCall->annotation()));
}

AST_CompositionElement Traverser::visitCompositionElement(AST_CompositionElement comp){
	AST_CompositionEqsAlgs compAlg= comp->getEquationsAlgs();
	AST_ElementList elList= comp->getElementList();
	if(compAlg){
		return new AST_CompositionElement_(visitCompositionEqsAlgs(compAlg));
	}else{
		return new AST_CompositionElement_(visitElementList(elList));
	}
}

AST_CompositionEqsAlgs Traverser::visitCompositionEqsAlgs(AST_CompositionEqsAlgs eqAlgs){
	AST_EquationList eqList = eqAlgs->getEquations();
	AST_StatementList stList = eqAlgs->getAlgorithms();
	if(eqList->size() > 0){
		return new AST_CompositionEqsAlgs_ (
			visitEquationList(eqList), eqAlgs->isInitial());
	}else{
		return new AST_CompositionEqsAlgs_ (
			visitStatementList(stList), eqAlgs->isInitial());
	}
}

AST_StatementList Traverser::visitStatementList(AST_StatementList stList){
	AST_StatementListIterator it;
	AST_StatementList ret = new list<AST_Statement>();
	foreach(it, stList){
		ret->insert(ret->end(), visitStatement(current_element(it)));
	}
	return ret;
}

AST_Statement Traverser::visitStatement(AST_Statement st){
	switch (st->statementType()){
	case STWHILE:
		return visitStatement_While(st->getAsWhile());
	case STIF:
		return visitStatement_If(st->getAsIf());
	case STWHEN:
		return visitStatement_When(st->getAsWhen());
	case STASSING:
		return visitStatement_Assign(st->getAsAssign());
	case STFOR:
		return visitStatement_For(st->getAsFor());
	case STOUTASSING:
	case STNONE:
	case STRETURN:
	case STBREAK:
	default:
		return st;
	}
}

AST_Statement_While Traverser::visitStatement_While(AST_Statement_While stWhile){
	return new AST_Statement_While_ (
		visitExpression(stWhile->condition()),
		visitStatementList(stWhile->statements()));
}

AST_Statement_If Traverser::visitStatement_If(AST_Statement_If stIf){
	return new AST_Statement_If_ (
		visitExpression(stIf->condition()), 
		visitStatementList(stIf->statements()),
		visitStatement_ElseList(stIf->else_if()), 
		visitStatementList(stIf->else_statements()));
}

AST_Statement_ElseList Traverser::visitStatement_ElseList(AST_Statement_ElseList stElseList){
	AST_Statement_ElseListIterator it;
	AST_Statement_ElseList ret = new list<AST_Statement_Else>();
	foreach(it, stElseList){
		ret->insert(ret->end(), visitStatement_Else(current_element(it)));
	}
	return ret;
}
AST_Statement_Else Traverser::visitStatement_Else(AST_Statement_Else stElse){
	return new AST_Statement_Else_(
		visitExpression(stElse->condition()), 
		visitStatementList(stElse->statements()));
}

AST_Statement_When Traverser::visitStatement_When(AST_Statement_When stWhen){
	return new AST_Statement_When_(
		visitExpression(stWhen->condition()), 
		visitStatementList(stWhen->statements()), 
		visitStatement_ElseList(stWhen->else_when()));
}

AST_Statement_Assign Traverser::visitStatement_Assign(AST_Statement_Assign stAssign){
	return new AST_Statement_Assign_(
		visitExpression_ComponentReference(stAssign->lhs()), 
		visitExpression(stAssign->exp()));
}

AST_Statement_For Traverser::visitStatement_For(AST_Statement_For stFor){
	return new AST_Statement_For_(
		visitForIndexList(stFor->forIndexList()), 
		visitStatementList(stFor->statements()));
}

AST_CompositionElementList Traverser::visitCompositionElementList(AST_CompositionElementList compList){
	AST_CompositionElementListIterator it;
	AST_CompositionElementList ret = new list<AST_CompositionElement>();
	foreach(it, compList){
		ret->insert(ret->end(), visitCompositionElement(current_element(it)));
	}
	return ret;
}

AST_EquationList Traverser::visitEquationList(AST_EquationList eqList){
	AST_EquationListIterator it;
	AST_EquationList ret = new list<AST_Equation>();
	foreach(it, eqList){
		ret->insert(ret->end(), visitEquation(current_element(it)));
	}
	return ret;
}

AST_Equation Traverser::visitEquation(AST_Equation eq){
	switch(eq->equationType()){
	case EQEQUALITY:
		return visitEquation_Equality(eq->getAsEquality());
	case EQCALL:
		return visitEquation_Call(eq->getAsCall());
	case EQFOR:
		return visitEquation_For(eq->getAsFor());
	case EQWHEN:
		return visitEquation_When(eq->getAsWhen());
	case EQIF:
		return visitEquation_If(eq->getAsIf());
	case EQCONNECT: 
		//undefined reference to AST_Equation_::getAsConnect
		//return visitEquation_Connect(eq->getAsConnect());  
	case EQNONE:
	default :
		return eq;
	}
}

AST_Equation_Call Traverser::visitEquation_Call(AST_Equation_Call eqCall){
	return new AST_Equation_Call_ (visitExpression(eqCall->call()));
}

AST_Equation_Connect Traverser::visitEquation_Connect(AST_Equation_Connect eqCon){
	return new AST_Equation_Connect_ (
		visitExpression_ComponentReference(eqCon->left()),
		visitExpression_ComponentReference(eqCon->right()));
}

AST_Equation_Equality Traverser::visitEquation_Equality(AST_Equation_Equality eqExp){
	return new AST_Equation_Equality_ (
		visitExpression(eqExp->left()), 
		visitExpression(eqExp->right()));
}

AST_Equation_For Traverser::visitEquation_For(AST_Equation_For eqFor){
	return new AST_Equation_For_ (
		visitForIndexList(eqFor->forIndexList()),
		visitEquationList(eqFor->equationList()));
}

AST_ForIndexList Traverser::visitForIndexList(AST_ForIndexList forIndexList){
	AST_ForIndexListIterator it;
	AST_ForIndexList ret = new list<AST_ForIndex>();
	foreach(it, forIndexList){
		ret->insert(ret->end(), visitForIndex(current_element(it)));
	}
	return ret;
}

AST_ForIndex Traverser::visitForIndex(AST_ForIndex forIndex){
	return new AST_ForIndex_ (visitVariable(forIndex->variable()), 
				  visitExpression(forIndex->in_exp()));
}

AST_Equation_If Traverser::visitEquation_If(AST_Equation_If eqIf){
	return new AST_Equation_If_ (
		visitExpression(eqIf->condition()),
		visitEquationList(eqIf->equationList()),
		visitEquation_ElseList(eqIf->equationElseIf()),
		visitEquationList(eqIf->equationElseList())
		);
}

AST_Equation_ElseList Traverser::visitEquation_ElseList(AST_Equation_ElseList elseList){
	AST_Equation_ElseListIterator it;
	AST_Equation_ElseList ret = new list<AST_Equation_Else>();
	foreach(it, elseList){
		ret->insert(ret->end(), visitEquation_Else(current_element(it)));
	}
	return ret;
}

AST_Equation_Else Traverser::visitEquation_Else(AST_Equation_Else _else){
	return new AST_Equation_Else_(
		visitExpression(_else->condition()), 
		visitEquationList(_else->equations()));
}

AST_Equation_When Traverser::visitEquation_When(AST_Equation_When eqWhen){
	return new AST_Equation_When_ (
		visitExpression(eqWhen->condition()),
		visitEquationList(eqWhen->equationList()), 
		visitEquation_ElseList(eqWhen->equationElseWhen()));
}

AST_ElementList Traverser::visitElementList(AST_ElementList elementList){
	AST_ElementListIterator it;
	AST_ElementList ret = new list<AST_Element>(); 
	foreach(it, elementList){
		ret->insert(ret->end(), visitElement(current_element(it)));
        }

	return ret;
}

AST_Element Traverser::visitElement(AST_Element element){
	switch(element->elementType()){
	case COMPONENT:
		return visitElement_Component(element->getAsComponent());
	case IMPORT: 
		return visitElement_ImportClause(element->getAsImportClause());
	case EXTENDS: 
		return visitElement_ExtendsClause(element->getAsExtendsClause());
	case ELCLASS: 
		return visitElement_ClassWrapper(element->getAsClassWrapper());
	case ELNONE:
	default:
		return element;
	}
}

AST_Element_ClassWrapper Traverser::visitElement_ClassWrapper(AST_Element_ClassWrapper cw){ 
	return new AST_Element_ClassWrapper_ (visitClass(cw->getClass()));
}

AST_Element_Component Traverser::visitElement_Component(AST_Element_Component comp){
	return new AST_Element_Component_ (
		visitDeclarationList(comp->nameList()),
		comp->type(), 
		comp->typePrefix(), 
		visitExpressionList(comp->indexes()));
}

AST_Element_ExtendsClause Traverser::visitElement_ExtendsClause(AST_Element_ExtendsClause extends){ 
	return extends;
}

AST_Element_ImportClause Traverser::visitElement_ImportClause(AST_Element_ImportClause import){
	return import;
}

AST_DeclarationList Traverser::visitDeclarationList(AST_DeclarationList decList){
	AST_DeclarationListIterator it;
	AST_DeclarationList ret = new list<AST_Declaration>();
	foreach(it, decList){
		ret->insert(ret->end(), visitDeclaration(current_element(it)));
	}
	return ret;
}

AST_Declaration Traverser::visitDeclaration(AST_Declaration dec){
 	return new AST_Declaration_ (dec->name(), 
				visitExpressionList(dec->indexes()),
				visitModification(dec->modification()));
}


AST_Modification Traverser::visitModification(AST_Modification modif){
	if(modif){
		switch(modif->modificationType()){
		case MODEQUAL:{
			AST_Modification_Equal mo = modif->getAsEqual();
			return visitModification_Equal(mo);
			break;
		}
		case MODASSIGN:{
			AST_Modification_Assign mo = modif->getAsAssign();
			return visitModification_Assign(mo);
			break;
		}
		case MODCLASS:{
			AST_Modification_Class mo = modif->getAsClass();
			return visitModification_Class(mo);
			break;
		}
		case  MODNONE:
		default:
			throw modif->modificationType();
		}
	}
	return modif;
}

AST_Modification_Assign Traverser::visitModification_Assign(AST_Modification_Assign modAssig){
	return new AST_Modification_Assign_ (visitExpression(modAssig->exp()));
}

AST_Modification_Class Traverser::visitModification_Class(AST_Modification_Class modClass){
	return new AST_Modification_Class_ (
			visitArgumentList(modClass->arguments()),
			visitExpression(modClass->exp()));
}

AST_Modification_Equal Traverser::visitModification_Equal(AST_Modification_Equal modEq){
	return new AST_Modification_Equal_ (visitExpression(modEq->exp()));
}

AST_ArgumentList Traverser::visitArgumentList(AST_ArgumentList argList){
	AST_ArgumentListIterator it;
	AST_ArgumentList ret = new list<AST_Argument>();
	foreach(it, argList){
		ret->insert(ret->end(), visitArgument(current_element(it)));
	}
	return ret;
}
AST_Argument Traverser::visitArgument(AST_Argument arg){
	AST_Argument_Modification argMo = dynamic_cast<AST_Argument_Modification>(arg);
	AST_Argument_Redeclaration argRed = dynamic_cast<AST_Argument_Redeclaration>(arg);
	if(argMo){
		return visitArgument_Modification(argMo);
	}else if(argRed){
		return visitArgument_Redeclaration(argRed);
	}else{
		return arg;
	}
}
AST_Argument_Modification Traverser::visitArgument_Modification(AST_Argument_Modification argMod){
	return new AST_Argument_Modification_ (visitString(argMod->name()), 
					      visitModification(argMod->modification()));
}
AST_Argument_Redeclaration Traverser::visitArgument_Redeclaration(AST_Argument_Redeclaration argRed){
	return argRed;
}


AST_ExpressionList Traverser::visitExpressionList(AST_ExpressionList exList){
	AST_ExpressionListIterator it;
	AST_ExpressionList ret = new list<AST_Expression>();
	foreach(it, exList){
		ret->insert(ret->end(), visitExpression(current_element(it)));
	}
	return ret;
}

AST_Expression Traverser::visitExpression(AST_Expression ex){
	if(ex == NULL){
		return ex;
	}
	switch(ex->expressionType()){
        case EXPCOMPREF:
		return visitExpression_ComponentReference(ex->getAsComponentReference());
        case EXPBINOP:
		return visitExpression_BinOp(ex->getAsBinOp());
        case EXPDERIVATIVE:
		return visitExpression_Derivative(ex->getAsDerivative());
        case EXPIF:
		return visitExpression_If(ex->getAsIf());
        case EXPCALLARG:
		return visitExpression_CallArgs(ex->getAsCallArgs());
        case EXPBRACE:
		return visitExpression_Brace(ex->getAsBrace());
        case EXPCALL:
		return visitExpression_Call(ex->getAsCall());
        case EXPELSEIF:
		return visitExpression_If_ElseIf(ex->getAsElseIf());
        case EXPBOOLEAN:
		return visitExpression_Boolean(ex->getAsBoolean());
        case EXPSTRING:
		return visitExpression_String(ex->getAsString());
        case EXPREAL:
		return visitExpression_Real(ex->getAsReal());
        case EXPINTEGER:
		return visitExpression_Integer(ex->getAsInteger());
        case EXPBOOLEANNOT:
		return visitExpression_BooleanNot(ex->getAsBooleanNot());
        case EXPOUTPUT:
		return visitExpression_Output(ex->getAsOutput());
        case EXPRANGE:
		return visitExpression_Range(ex->getAsRange());
        case EXPUMINUS:
		return ex;
        case EXPEND:
		return ex;
        case EXPNULL:
		return ex;
        case EXPCOLON:
		return ex;
	case EXPNONE:
		return ex;
	default:
		return ex;
	}
}

AST_Expression_BinOp Traverser::visitExpression_BinOp(AST_Expression_BinOp binOp){
	return new AST_Expression_BinOp_ (
		visitExpression(binOp->left()), 
		visitExpression(binOp->right()), binOp->binopType());
}

AST_Expression_Boolean Traverser::visitExpression_Boolean (AST_Expression_Boolean boolean){
	return boolean;
}

AST_Expression_BooleanNot Traverser::visitExpression_BooleanNot(AST_Expression_BooleanNot notExp){
	return new AST_Expression_BooleanNot_ (visitExpression(notExp->exp()));
}

AST_Expression_Brace Traverser::visitExpression_Brace(AST_Expression_Brace brace){
	return new AST_Expression_Brace_ (visitExpressionList(brace->arguments()));
}

AST_Expression_Call Traverser::visitExpression_Call(AST_Expression_Call callExp){
	return new AST_Expression_Call_ (visitString(callExp->name()), 
					visitExpressionList(callExp->arguments()));
}

AST_Expression_CallArgs Traverser::visitExpression_CallArgs(AST_Expression_CallArgs callArgsExp){
	return new AST_Expression_CallArgs_ (visitExpressionList(callArgsExp->arguments()));
}

AST_Expression_ComponentReference Traverser::visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp){
	AST_Expression_ComponentReference rVal =
		 new AST_Expression_ComponentReference_ ();

	AST_StringListIterator it;
	AST_ExpressionListListIterator exp_it=compRefExp->indexes()->begin();
	foreach (it, compRefExp->names()) {
		rVal->append(visitString(current_element(it)), 
			visitExpressionList(current_element(exp_it)));
		exp_it++;
	}

	return rVal;
}

AST_Expression_Derivative Traverser::visitExpression_Derivative(AST_Expression_Derivative der){
	return new AST_Expression_Derivative_ (
		visitExpressionList(der->arguments()));
}

AST_Expression_End Traverser::visitExpression_End(AST_Expression_End endStm){
	return endStm;
}

AST_Expression_If Traverser::visitExpression_If(AST_Expression_If ifExp){
	return new AST_Expression_If_ (
		visitExpression(ifExp->condition()),
		visitExpression(ifExp->then()), 
		visitExpression(ifExp->else_exp()),
		visitExpressionList(ifExp->elseif_list()));
}

AST_Expression_If_ElseIf Traverser::visitExpression_If_ElseIf(AST_Expression_If_ElseIf elseIfExp){
  	return new AST_Expression_If_ElseIf_ (
		visitExpression(elseIfExp->condition()),
		visitExpression(elseIfExp->then()));
}

AST_Expression_Integer Traverser::visitExpression_Integer(AST_Expression_Integer expInt){
	return expInt;
}

AST_Expression_Null Traverser::visitExpression_Null(AST_Expression_Null nullExp){
	return nullExp;
}

AST_Expression_Output Traverser::visitExpression_Output(AST_Expression_Output outExp){
  	return new AST_Expression_Output_ (visitExpressionList(outExp->expressionList()));
	return outExp;
}

AST_Expression_Range Traverser::visitExpression_Range(AST_Expression_Range rangeExp){
	return new AST_Expression_Range_ (visitExpressionList(rangeExp->expressionList()));
}

AST_Expression_Real Traverser::visitExpression_Real(AST_Expression_Real realExp){
	return realExp;
}

AST_Expression_String Traverser::visitExpression_String(AST_Expression_String strExp){
	return strExp;
}

AST_Expression_UMinus Traverser::visitExpression_UMinus(AST_Expression_UMinus uminusExp){
	return new AST_Expression_UMinus_ (visitExpression(uminusExp->exp()));
}

AST_Element_ClassWrapper Traverser::visitClassWrapper(AST_Element_ClassWrapper classWrapExp){
 	return new AST_Element_ClassWrapper_ (visitClass(classWrapExp->getClass()));
}

AST_String Traverser::visitVariable(AST_String s){
	AST_String rtr = new string(*s);
	return rtr;
}
}
