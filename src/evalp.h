#ifndef PD2MO_EVALP
#define PD2MO_EVALP
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <traverser.h>
#include <string>

#include <QStringList>
#include <vector>

namespace pd2mo{
class evalp: public Traverser {
	QStringList params;
	std::vector<AST_Expression> *exp;
public:
	void setParams(QStringList x);
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
        AST_Expression visitExpression_ComponentReferenceALT(AST_Expression_ComponentReference compRefExp);
        virtual AST_String visitVariable(AST_String s);
	virtual AST_Expression visitExpression(AST_Expression ex);
};
}
#endif
