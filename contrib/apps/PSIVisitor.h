/*
 * PSIProcessor.h
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSIVISITOR_H_
#define SRC_APPS_PSIVISITOR_H_
#include "api/IModel.h"
#include "api/IBaseItem.h"

using namespace psi_api;

namespace psi {
namespace apps {

class PSIVisitor {

public:

	PSIVisitor();

	virtual ~PSIVisitor();

protected:
	virtual void visit_model(IModel *model);

	virtual void visit_package(IPackage *pkg);

	virtual void visit_action(IAction *a);

	virtual void visit_bind(IBind *b);

	virtual void visit_body(IBaseItem *p, const std::vector<IBaseItem *> &items);

	virtual void visit_struct(IStruct *str);

	virtual void visit_component(IComponent *c);

	virtual void visit_comp_pkg_body(const std::vector<IBaseItem *> &items);

	virtual void visit_constraint(IConstraintBlock *c);

	virtual void visit_constraint_stmt(IConstraint *c);

	virtual void visit_constraint_expr_stmt(IConstraintExpr *c);

	virtual void visit_constraint_block(IConstraintBlock *block);

	virtual void visit_expr(IExpr *e);

	virtual void visit_binary_expr(IBinaryExpr *be);

	virtual void visit_fieldref_expr(IFieldRef *ref);

	virtual void visit_literal_expr(ILiteral *l);

	virtual void visit_field(IField *f);

	virtual void visit_graph(IGraphStmt *graph);

	virtual void visit_graph_stmt(IGraphStmt *stmt);

	virtual void visit_graph_block_stmt(IGraphBlockStmt *block);

	static std::string type2string(IBaseItem *it);

	static std::string path2string(IFieldRef *f);

	static std::string path2string(const std::vector<IField *> &path);

};

} /* namespace apps */
} /* namespace psi */

#endif /* SRC_APPS_PSIVISITOR_H_ */
