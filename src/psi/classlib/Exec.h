/*
 * Exec.h
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

#ifndef SRC_CLASSLIB_EXEC_H_
#define SRC_CLASSLIB_EXEC_H_

#include <string>

#include "classlib/Type.h"
#include "classlib/NativeExecClosure.h"
#include "classlib/SharedPtr.h"

namespace psi {

class ImportCall;

class Exec : public Type {

	public:
		enum ExecKind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};
		enum ExecType {
			Null,
			TargetTemplate,
			Native,
			Inline
		};

	public:

		Exec(
			ExecKind 				kind,
			Type					*p,
			const std::string 		&language,
			const std::string 		&content);

		Exec(
			ExecKind 				kind,
			Type					*p,
			const ImportCall		&call);

		Exec(
			ExecKind								kind,
			Type									*p,
			const SharedPtr<NativeExecClosureBase>	&closure,
			const std::vector<Type *>				&write_vars);

		virtual ~Exec();


		inline ExecKind getExecKind() const {
			return m_execKind;
		}

		inline ExecType getExecType() const {
			return m_execType;
		}

	private:
		ExecType							m_execType;
		ExecKind							m_execKind;
		std::string							m_language;
		std::string							m_content;
		SharedPtr<NativeExecClosureBase>	m_closure;


};

} /* namespace psi */

#endif /* SRC_CLASSLIB_EXEC_H_ */
