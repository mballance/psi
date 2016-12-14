/*
 * exec.cpp
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include <stdio.h>

#include "ExecImp.h"
#include "classlib/ExtendItem.h"
#include "classlib/ExecStmtList.h"

namespace pss {

exec::exec(
		BaseItem				*p,
		exec::ExecKind			kind,
		const std::string 		&language,
		const std::string 		&content) :
	BaseItem(new ExecImp(this, p, kind, language, content)) { }

ExecImp::ExecImp(
		exec					*master,
		BaseItem				*p,
		exec::ExecKind 			kind,
		const std::string 		&language,
		const std::string		&content) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) { }

exec::exec(
		ExtendItem				*p,
		ExecKind 				kind,
		const std::string 		&language,
		const std::string 		&content) :
	BaseItem(new ExecImp(this, p, kind, language, content)) { }

ExecImp::ExecImp(
		exec					*master,
		ExtendItem				*p,
		exec::ExecKind 			kind,
		const std::string 		&language,
		const std::string 		&content) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) { }

exec::exec(
		BaseItem				*p,
		ExecKind 				kind,
		const ExecStmtList		&stmts) :
			BaseItem(new ExecImp(this, p, kind, stmts)) { }

ExecImp::ExecImp(
		exec					*master,
		ExtendItem				*p,
		exec::ExecKind 			kind,
		const ExecStmtList		&stmts) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_stmts(stmts) {
	// TODO: save call information
	fprintf(stdout, "ExecImp::ExecImp Native\n");
}

ExecImp::ExecImp(
		exec					*master,
		BaseItem				*p,
		exec::ExecKind 			kind,
		const ExecStmtList		&stmts) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_stmts(stmts) {
	// TODO: save call information
	fprintf(stdout, "ExecImp::ExecImp Native\n");
}

exec::exec(
		BaseItem								*p,
		ExecKind								kind) :
	BaseItem(new ExecImp(this, p, kind)) { }

ExecImp::ExecImp(
		exec									*master,
		BaseItem								*p,
		exec::ExecKind							kind) :
				BaseItemImp(master, BaseItemImp::TypeExec, p),
				m_execType(Inline),
				m_execKind(kind) {
	// TODO: save write vars
	fprintf(stdout, "ExecImp::ExecImp Inline\n");
}

exec::~exec() {
	// TODO Auto-generated destructor stub
}

ExecImp::~ExecImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
