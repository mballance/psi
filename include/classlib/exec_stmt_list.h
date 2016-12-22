/*
 * exec_stmt_list.h
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
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_CLASSLIB_EXECSTMTLIST_H_
#define INCLUDE_CLASSLIB_EXECSTMTLIST_H_
#include "classlib/pss_types.h"
#include "classlib/exec_stmt.h"
#include "classlib/exec_import_call_stmt.h"

namespace pss {

class ExecStmtListImp;
class exec_stmt_list {
public:

	exec_stmt_list();

	exec_stmt_list(const exec_stmt_list &rhs);

#ifdef PSS_HAVE_CXX_11
	exec_stmt_list(std::initializer_list<exec_stmt> l) : exec_stmt_list() {
		exec_stmt_list &el = *this;

		for (std::initializer_list<exec_stmt>::const_iterator it=l.begin();
				it!=l.end(); it++) {
			el = (el, *it);
		}
	}

	template <typename T, typename... R> static exec_stmt_list mklist(
			const T			&item,
			const R&...		rest) {
		exec_stmt_list el;
		return _mklist(el, item, rest...);
	}
#endif

	exec_stmt_list(const exec_stmt &rhs);

	virtual ~exec_stmt_list();

	exec_stmt_list operator,(const exec_stmt &rhs);

	ExecStmtListImp *imp() const;

private:
	exec_stmt_list(ExecStmtListImp *imp);

#ifdef PSS_HAVE_CXX_11
	template <typename T, typename... R> static exec_stmt_list &_mklist(
			exec_stmt_list		&el,
			const T				&item,
			const R&...			rest) {
		el = (el, item);

		return _mklist(el, rest...);
	}

	static exec_stmt_list &_mklist(exec_stmt_list &el) {
		return el;
	}
#endif


private:
	ExecStmtListImp				*m_imp;

};

}




#endif /* INCLUDE_CLASSLIB_EXECSTMTLIST_H_ */
