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

#include "classlib/Exec.h"

namespace psi {

//Exec::Exec() : m_execType(Null) { }

Exec::Exec(
		Type					*p,
		ExecKind 				kind,
		const std::string 		&language,
		const std::string 		&content) :
			Type(Type::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content),
			m_closure(0) {
}

Exec::Exec(
		Type					*p,
		ExecKind 				kind,
		const ExprList			&stmts) :
			Type(Type::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_stmts(stmts),
			m_closure(0) {
	// TODO: save call information
}

Exec::Exec(
		Type									*p,
		ExecKind								kind,
		const SharedPtr<NativeExecClosureBase>	&closure,
		const std::vector<Type *>				&write_vars) :
				Type(Type::TypeExec, p),
				m_execType(Inline),
				m_execKind(kind),
				m_closure(closure) {

}

Exec::~Exec() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
