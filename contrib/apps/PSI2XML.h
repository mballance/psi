/*
 * PSI2XML.h
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
 * Traverses a Semantic Model description using the PSI API
 * and writes an XML file as output
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSI2XML_H_
#define SRC_APPS_PSI2XML_H_
#include <string>
#include <vector>
#include <stdint.h>

#include "api/IModel.h"
#include "api/IBaseItem.h"

using namespace psi_api;

namespace psi {
namespace apps {

class PSI2XML {
public:
	PSI2XML();

	virtual ~PSI2XML();

	void setUseFixedInlineAddr() { m_fixed_inline_addr = true; }

	virtual const std::string &traverse(IModel *model);


private:

	void process_pkg(IPackage *pkg);

	void process_action(IAction *a);

	void process_bind(IBind *b);

	void process_body(
			const std::vector<IBaseItem *>  &items,
			const std::string				&ctxt);

	void process_exec(IExec *exec);

	void process_struct(IStruct *str);

	void process_component(IComponent *c);

	void process_comp_pkg_body(const std::vector<IBaseItem *> &items);

	void process_constraint(IConstraint *c);

	void process_constraint_set(IConstraint *c, const char *tag=0);

	void process_constraint_block(IConstraintBlock *block);

	void process_expr(IExpr *e, const char *tag=0);

	void process_field(IField *f);

	void process_graph(IGraphStmt *graph);

	void process_graph_stmt(IGraphStmt *stmt, const char *tag=0);

	void process_graph_block_stmt(IGraphBlockStmt *block, const char *tag=0);

	static std::string type2string(IBaseItem *it);

	void type2hierarchical_id(IBaseItem *it, const std::string &tag="pss:type");

	void type2data_type(IBaseItem *it, const std::string &tag="pss:type");

	void to_hierarchical_id(const std::vector<IBaseItem *> &path, const char *tag=0);

	static std::string path2string(IFieldRef *f);

	void println(const std::string &str);

	void inc_indent();
	void dec_indent();

	void enter(const std::string &str);

	void exit(const std::string &str);

	void error(const char *fmt, ...);

	static INamedItem *toNamedItem(IBaseItem *it);

private:
	std::string					m_ind;
	uint32_t					m_ind_incr;
	std::string					m_content;
	bool						m_fixed_inline_addr;


};

}
}

#endif /* SRC_APPS_PSI2XML_H_ */
