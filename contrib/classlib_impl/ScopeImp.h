/*
 * scope.h
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
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_IMP_H
#define INCLUDED_SCOPE_IMP_H
#include <string>
#include <vector>
#include <typeinfo>

#include "classlib/scope.h"

namespace pss {

class BaseItemImp;
class scope;
class ScopeImp {
public:
	friend scope;
	ScopeImp(
			scope 					*master,
			const std::type_info	*type,
			base_item 				*ctxt,
			bool					is_field,
			bool					is_type,
			const std::string		&name,
			base_item				*type_id);

	ScopeImp(base_item				*ctxt);

	virtual ~ScopeImp();

	base_item *parent() const;

	base_item *ctxt() const { return m_ctxt; }

	void set_ctxt(base_item *ctxt) { m_ctxt = ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	const char *scope_name() const { return m_name.c_str(); }

	void set_scope_name(const std::string &name);

	bool is_field() const { return m_is_field; }

	bool is_type() const { return m_is_type; }

	base_item *type_id() const { return m_type_id; }

private:

	void enter();

	void leave();

private:
	scope					*m_master;
	bool					m_is_field;
	bool					m_is_type;
	base_item				*m_ctxt;
	const std::type_info	*m_type;
	std::string				m_name;
	base_item				*m_type_id;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
