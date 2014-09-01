#ifndef PD2MO_EVALP
#define PD2MO_EVALP
#include <ast/stored_definition.h>
#include <ast/modification.h>
#include <parser/parse.h>
#include <traverser.h>
#include <string>

#include <QStringList>

namespace pd2mo{
class evalp: public Traverser {
	QStringList params;
	void setParams(QStringList x){ params = x; }
	virtual AST_Declaration visitDeclaration(AST_Declaration dec);
        virtual AST_Expression_ComponentReference visitExpression_ComponentReference(AST_Expression_ComponentReference compRefExp);
        virtual AST_String visitVariable(AST_String s);
};
}
#endif
