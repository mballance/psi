/*
 * PsiElaborator.h
 *
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_ELABORATOR_ELABORATOR_H_
#define SRC_ELABORATOR_ELABORATOR_H_
#include <vector>
#include <stdarg.h>

#include "api/IAction.h"
#include "api/IBind.h"
#include "api/IConstraint.h"
#include "api/IConstraintIf.h"
#include "api/IExpr.h"
#include "api/IExec.h"
#include "api/IGraphStmt.h"
#include "api/IModel.h"
#include "api/IPackage.h"
#include "classlib/Action.h"
#include "classlib/Bind.h"
#include "classlib/Component.h"
#include "classlib/Constraint.h"
#include "classlib/Graph.h"
#include "classlib/FieldItem.h"
#include "classlib/Package.h"
#include "classlib/BaseItem.h"
#include "classlib/Struct.h"
#include "classlib/Exec.h"
#include "ExprIfImp.h"

using namespace psi_api;

namespace psi {

class Elaborator {
public:

	enum LogLevel {
		OFF,
		LOW,
		MED,
		HIGH
	};

public:

	Elaborator();

	virtual ~Elaborator();

	void set_log_level(LogLevel l) { m_log_level = l; }

	void elaborate(BaseItem *root, IModel *model);

protected:

	IAction *elaborate_action(Action *a);

	IComponent *elaborate_component(IScopeItem *scope, Component *c);

	IBind *elaborate_bind(Bind *b);

	IConstraint *elaborate_constraint(Constraint *c);

	IConstraintIf *elaborate_constraint_if(ExprCoreIf *if_c);

	IExpr *elaborate_expr(ExprCore *e);

	IConstraint *elaborate_constraint_stmt(ExprCore *s);

	IStruct *elaborate_struct(Struct *str);

	void elaborate_package(IModel *model, Package *pkg_cl);

	IBaseItem *elaborate_struct_action_body_item(BaseItem *t);

	IExec *elaborate_exec_item(Exec *e);

	IField *elaborate_field_item(FieldItem *f);

	IFieldRef *elaborate_field_ref(BaseItem *ref);

	IBindPath *elaborate_bind_path(BaseItem *it);

	IGraphStmt *elaborate_graph(Graph *g);

	IGraphStmt *elaborate_graph_stmt(ExprCore *stmt);


private:

private:

	void set_expr_ctxt(IBaseItem *model_ctxt, BaseItem *class_ctxt);

	static IField::FieldAttr getAttr(FieldItem *t);

	BaseItem *find_cl_type_decl(const TypePath &t);

	IBaseItem *find_type_decl(const TypePath &t);

	IBaseItem *find_type_decl(BaseItem *t);

	static IBaseItem *find_named_scope(
			const std::vector<IBaseItem *> 	&list,
			const std::string 				&name);

	bool should_filter(
			const std::vector<BaseItem *>		&items,
			uint32_t						i,
			const std::vector<BaseItem *>		&type_h);

	void build_type_hierarchy(
			std::vector<BaseItem *>				&type_h,
			BaseItem							*t);

	static IScopeItem *toScopeItem(IBaseItem *it);
	static INamedItem *toNamedItem(IBaseItem *it);

	static const char *getName(IBaseItem *it);

	static IScopeItem *getSuperType(IScopeItem *it);

	static NamedBaseItem *toNamedItem(BaseItem *it);

	void error(const char *fmt, ...);

	void error(const std::string &msg);

	void debug(LogLevel l, const char *fmt, ...);

	void debug(LogLevel l, const char *fmt, va_list ap);

	void debug_low(const char *fmt, ...);

	void debug_med(const char *fmt, ...);

	void debug_high(const char *fmt, ...);

private:
	IBaseItem				*m_model_expr_ctxt;
	BaseItem				*m_class_expr_ctxt;
	IModel					*m_model;

	LogLevel				m_log_level;



};

} /* namespace psi */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
