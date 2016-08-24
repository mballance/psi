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
#include "ActionImp.h"
#include "BindImp.h"
#include "ComponentImp.h"
#include "ConstraintImp.h"
#include "ExtendItemImp.h"
#include "GraphImp.h"
#include "FieldItemImp.h"
#include "ImportImp.h"
#include "PackageImp.h"
#include "BaseItemImp.h"
#include "StructImp.h"
#include "ExecImp.h"
#include "ExprCoreIf.h"
#include "TypePathImp.h"
#include "NamedBaseItemImp.h"

using namespace psi_api;

namespace pss {

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

	void elaborate(BaseItemImp *root, IModel *model);

protected:

	IAction *elaborate_action(ActionImp *a);

	IComponent *elaborate_component(IScopeItem *scope, ComponentImp *c);

	IBaseItem *elaborate_component_body_item(BaseItemImp *t);

	IBind *elaborate_bind(BindImp *b);

	IConstraint *elaborate_constraint(ConstraintImp *c);

	IConstraintIf *elaborate_constraint_if(ExprCoreIf *if_c);

	IExpr *elaborate_expr(ExprCore *e);

	IConstraint *elaborate_constraint_stmt(ExprCore *s);

	IStruct *elaborate_struct(StructImp *str);

	void elaborate_package(IModel *model, PackageImp *pkg_cl);

	IBaseItem *elaborate_struct_action_body_item(BaseItemImp *t);


	IExec *elaborate_exec_item(ExecImp *e);

	IExtend *elaborate_extend(ExtendItemImp *e);

	IField *elaborate_field_item(FieldItemImp *f);

	IFieldRef *elaborate_field_ref(BaseItemImp *ref);

	IImportFunc *elaborate_import_func(ImportImp *imp);

	IBindPath *elaborate_bind_path(BaseItemImp *it);

	IGraphStmt *elaborate_graph(GraphImp *g);

	IGraphStmt *elaborate_graph_stmt(ExprCore *stmt);


private:

private:

	void set_expr_ctxt(IBaseItem *model_ctxt, BaseItemImp *class_ctxt);

	static IField::FieldAttr getAttr(FieldItemImp *t);

	BaseItemImp *find_cl_type_decl(const TypePathImp &t);

	IBaseItem *find_type_decl(const TypePathImp &t);

	IBaseItem *find_type_decl(BaseItemImp *t);

	static IBaseItem *find_named_scope(
			const std::vector<IBaseItem *> 	&list,
			const std::string 				&name);

	bool should_filter(
			const std::vector<BaseItemImp *>	&items,
			uint32_t							i,
			const std::vector<BaseItemImp *>	&type_h);

	void build_type_hierarchy(
			std::vector<BaseItemImp *>			&type_h,
			BaseItemImp							*t);

	static IScopeItem *toScopeItem(IBaseItem *it);
	static INamedItem *toNamedItem(IBaseItem *it);

	static const char *getName(IBaseItem *it);

	static const char *getName(IScopeItem *it);

	static IScopeItem *getSuperType(IScopeItem *it);

	static NamedBaseItemImp *toNamedItem(BaseItemImp *it);

	void error(const char *fmt, ...);

	void error(const std::string &msg);

	void debug(LogLevel l, const char *fmt, ...);

	void debug(LogLevel l, const char *fmt, va_list ap);

	void debug_low(const char *fmt, ...);

	void debug_med(const char *fmt, ...);

	void debug_high(const char *fmt, ...);

private:
	IBaseItem				*m_model_expr_ctxt;
	BaseItemImp				*m_class_expr_ctxt;
	IModel					*m_model;

	LogLevel				m_log_level;



};

} /* namespace pss */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
