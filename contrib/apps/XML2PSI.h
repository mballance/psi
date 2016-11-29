/*
 * XML2PSI.h
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
 *  Created on: May 17, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_XML2PSI_H_
#define SRC_APPS_XML2PSI_H_
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <stack>
#include <map>

#include "psi_api.h"

using namespace psi_api;

namespace psi {
namespace apps {

class XML2PSI {
public:
	XML2PSI();

	virtual ~XML2PSI();

	virtual void process(const std::string &content, IModel *model);

protected:
	typedef std::pair<std::string,std::string> strpair;

	typedef std::map<std::string,std::string> strmap;
	typedef std::pair<std::string,std::string> strmap_ent;

	void elaborate_model(xmlNode *m);

	IAction *elaborate_action(xmlNode *p, const strmap &attr);

	IComponent *elaborate_component(xmlNode *p, const strmap &attr);

	IConstraint *elaborate_constraint_set(xmlNode *p, const strmap &attr);

	IConstraintBlock *elaborate_constraint_declaration(xmlNode *p, const strmap &attr);

	IExec *elaborate_exec(xmlNode *p, const strmap &attr);

	IExpr *elaborate_expr(xmlNode *p, const strmap &attr);

	IField *elaborate_field(xmlNode *p, const strmap &attr);

	IFieldRef *elaborate_field_ref(xmlNode *p);

	IImportFunc *elaborate_import_function(xmlNode *p, const strmap &attr);

	void elaborate_import_stmt(xmlNode *p, const strmap &attr);

	IField *elaborate_parameter(xmlNode *p, const strmap &attr);

	IBaseItem *elaborate_type(xmlNode *p, const strmap &attr);

	void elaborate_package(xmlNode *p, const strmap &attr);

	IStruct *elaborate_struct(xmlNode *p, const strmap &attr);

	IBaseItem *elaborate_action_struct_component_item(xmlNode *p, const strmap &attr);

	IFieldRef *elaborate_variable_ref(xmlNode *p);

	IBaseItem *find_type(IScopeItem *curr, const std::vector<std::string> &path);

	IField *find_field(const std::string &name);

	std::vector<std::string> split_path(const std::string &path);

private:
	class Context {
	public:

		Context(IBaseItem *scope) : m_scope(scope) { }

		IBaseItem *scope() const { return m_scope; }

		void add_import(IBaseItem *imp) {
			m_imports.push_back(imp);
		}

		const std::vector<IBaseItem *> &imports() const {
			return m_imports;
		}

	private:

		IBaseItem						*m_scope;
		std::vector<IBaseItem *>		m_imports;
	};

private:

	static void get_attributes(xmlNode *n, strmap &attr);

	static IExecExprStmt::AssignOp toAssignOp(const std::string &op);

	static IBinaryExpr::BinOpType toBinOp(const std::string &op);

	IBaseItem *find_type(xmlNode *p);


private:

	IModel								*m_model;
	std::stack<Context>					m_scope_stack;

};

}
} /* namespace psi */

#endif /* SRC_APPS_XML2PSI_H_ */
