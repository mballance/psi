/*
 * import_func.cpp
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "ImportFuncImp.h"
#include "classlib/expr_list.h"
#include "classlib/chandle_type.h"
#include "ExecImportCallStmtImp.h"
#include "FieldItemImp.h"


namespace pss {

import_func::import_func(
		base_item 				*p,
		const std::string 		&name,
		const method_param_list 	&plist) :
	base_item(new ImportFuncImp(this, p, name, plist)) {
}

ImportFuncImp::ImportFuncImp(
		import_func				*master,
		base_item 				*p,
		const std::string 		&name,
		const method_param_list 	&plist) :
	NamedBaseItemImp(master, BaseItemImp::TypeImport, p, name),
	m_have_ret(false), m_ret(chandle_type(std::string("void"))), m_parameters(plist) {

	// Unlink the parameters from the parent, since the scope parent
	// is the containing package/component
	MethodParamListImp *plist_i = static_cast<MethodParamListImp *>(plist.imp());
	for (std::vector<attr_item>::const_iterator it=plist_i->parameters().begin();
			it!=plist_i->parameters().end(); it++) {
		FieldItemImp *imp = static_cast<FieldItemImp *>((*it).impl());
		if (imp->getParent()) {
			imp->getParent()->remove(imp);
		}
	}
}

import_func::import_func(
		base_item 				*p,
		const std::string 		&name,
		const base_item 			&ret,
		const method_param_list	&plist) :
	base_item(new ImportFuncImp(this, p, name, ret, plist)) {

}

ImportFuncImp::ImportFuncImp(
		import_func					*master,
		base_item 				*p,
		const std::string 		&name,
		const base_item 			&ret,
		const method_param_list	&plist) :
	NamedBaseItemImp(master, BaseItemImp::TypeImport, p, name),
	m_have_ret(true), m_ret(ret), m_parameters(plist) {

	// Unlink the parameters from the parent, since the scope parent
	// is the containing package/component
	MethodParamListImp *plist_i = static_cast<MethodParamListImp *>(plist.imp());
	for (std::vector<attr_item>::const_iterator it=plist_i->parameters().begin();
			it!=plist_i->parameters().end(); it++) {
		FieldItemImp *imp = static_cast<FieldItemImp *>((*it).impl());
		if (imp->getParent()) {
			imp->getParent()->remove(imp);
		}
	}
}

import_func::~import_func() {
	// TODO Auto-generated destructor stub
}

ImportFuncImp::~ImportFuncImp() {
	// TODO Auto-generated destructor stub
}

exec_import_call_stmt import_func::operator()(const expr_list &plist) {
	return exec_import_call_stmt(*this, plist);
}

exec_import_call_stmt import_func::operator()() {
	return exec_import_call_stmt(*this, expr_list());
}

} /* namespace pss */
