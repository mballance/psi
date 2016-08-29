/*
 * ImportFunc.cpp
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "ImportFuncImp.h"
#include "classlib/ExprList.h"
#include "classlib/ChandleType.h"


namespace pss {

ImportFunc::ImportFunc(
		BaseItem 				*p,
		const std::string 		&name,
		const MethodParamList 	&plist) :
	BaseItem(new ImportFuncImp(this, p, name, plist)) {

}

ImportFuncImp::ImportFuncImp(
		ImportFunc					*master,
		BaseItem 				*p,
		const std::string 		&name,
		const MethodParamList 	&plist) :
	NamedBaseItemImp(master, BaseItemImp::TypeImport, p, name),
	m_have_ret(false), m_ret(ChandleType(std::string("void"))), m_parameters(plist) {

}

ImportFunc::ImportFunc(
		BaseItem 				*p,
		const std::string 		&name,
		const BaseItem 			&ret,
		const MethodParamList	&plist) :
	BaseItem(new ImportFuncImp(this, p, name, ret, plist)) {

}

ImportFuncImp::ImportFuncImp(
		ImportFunc					*master,
		BaseItem 				*p,
		const std::string 		&name,
		const BaseItem 			&ret,
		const MethodParamList	&plist) :
	NamedBaseItemImp(master, BaseItemImp::TypeImport, p, name),
	m_have_ret(true), m_ret(ret), m_parameters(plist) {
}

ImportFunc::~ImportFunc() {
	// TODO Auto-generated destructor stub
}

ImportFuncImp::~ImportFuncImp() {
	// TODO Auto-generated destructor stub
}

ExecImportCallStmt ImportFunc::operator()(const ExprList &plist) {
	return ExecImportCallStmt(*this, plist);
}

ExecImportCallStmt ImportFunc::operator()() {
	return ExecImportCallStmt(*this, ExprList());
}

} /* namespace pss */
