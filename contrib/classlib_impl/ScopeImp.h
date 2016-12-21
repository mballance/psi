/*
 * Scope.h
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

#include "classlib/Scope.h"

namespace pss {

class BaseItemImp;
class Scope;
class ScopeImp {
public:
	friend Scope;
	ScopeImp(
			Scope 					*master,
			const std::type_info	*type,
			BaseItem 				*ctxt,
			bool					is_field,
			bool					is_type,
			const std::string		&name,
			BaseItem				*type_id);

	ScopeImp(BaseItem				*ctxt);

	virtual ~ScopeImp();

	BaseItem *parent() const;

	BaseItem *ctxt() const { return m_ctxt; }

	void set_ctxt(BaseItem *ctxt) { m_ctxt = ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	const char *scope_name() const { return m_name.c_str(); }

	void set_scope_name(const std::string &name);

	bool is_field() const { return m_is_field; }

	bool is_type() const { return m_is_type; }

	BaseItem *type_id() const { return m_type_id; }

private:

	void enter();

	void leave();

private:
	Scope					*m_master;
	bool					m_is_field;
	bool					m_is_type;
	BaseItem				*m_ctxt;
	const std::type_info	*m_type;
	std::string				m_name;
	BaseItem				*m_type_id;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
