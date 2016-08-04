/*
 * Exec.cpp
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

#include <stdio.h>

#include "ExecImp.h"
#include "classlib/ExtendItem.h"

namespace pss {

Exec::Exec(
		BaseItem				*p,
		Exec::ExecKind			kind,
		const std::string 		&language,
		const std::string 		&content) :
	BaseItem(new ExecImp(this, p, kind, language, content)) { }

ExecImp::ExecImp(
		Exec					*master,
		BaseItem				*p,
		Exec::ExecKind 			kind,
		const std::string 		&language,
		const std::string		&content) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) { }

Exec::Exec(
		ExtendItem				*p,
		ExecKind 				kind,
		const std::string 		&language,
		const std::string 		&content) :
	BaseItem(new ExecImp(this, p, kind, language, content)) { }

ExecImp::ExecImp(
		Exec					*master,
		ExtendItem				*p,
		Exec::ExecKind 			kind,
		const std::string 		&language,
		const std::string 		&content) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) { }

Exec::Exec(
		BaseItem				*p,
		ExecKind 				kind,
		const ExprList			&stmts) :
			BaseItem(new ExecImp(this, p, kind, stmts)) { }

ExecImp::ExecImp(
		Exec					*master,
		ExtendItem				*p,
		Exec::ExecKind 			kind,
		const ExprList			&stmts) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_stmts(stmts) {
	// TODO: save call information
	fprintf(stdout, "ExecImp::ExecImp Native\n");
}

ExecImp::ExecImp(
		Exec					*master,
		BaseItem				*p,
		Exec::ExecKind 			kind,
		const ExprList			&stmts) :
			BaseItemImp(master, BaseItemImp::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_stmts(stmts) {
	// TODO: save call information
	fprintf(stdout, "ExecImp::ExecImp Native\n");
}

Exec::Exec(
		BaseItem								*p,
		ExecKind								kind) :
	BaseItem(new ExecImp(this, p, kind)) { }

ExecImp::ExecImp(
		Exec									*master,
		BaseItem								*p,
		Exec::ExecKind							kind) :
				BaseItemImp(master, BaseItemImp::TypeExec, p),
				m_execType(Inline),
				m_execKind(kind) {
	// TODO: save write vars
	fprintf(stdout, "ExecImp::ExecImp Inline\n");
}

Exec::~Exec() {
	// TODO Auto-generated destructor stub
}

ExecImp::~ExecImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
