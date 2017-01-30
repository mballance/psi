/*
 * PSI2PSS.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSI2PSS_H_
#define SRC_APPS_PSI2PSS_H_
#include "PSI2StringProcessor.h"

namespace psi {
namespace apps {

class PSI2PSS : public PSI2StringProcessor {
public:
	PSI2PSS();

	virtual ~PSI2PSS();

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

	virtual void visit_graph(IGraphStmt *activity);

	virtual void visit_graph_stmt(IGraphStmt *stmt);

	virtual void visit_graph_block_stmt(IGraphBlockStmt *block);

	static std::string get_field_typename(IField *f);

	static std::string binop_tostring(IBinaryExpr::BinOpType t);



};

} /* namespace apps */
} /* namespace psi */

#endif /* SRC_APPS_PSI2PSS_H_ */
