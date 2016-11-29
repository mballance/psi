/*
 * ExecStmtList.h
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
#include "classlib/Types.h"
#include "classlib/ExecStmt.h"
#include "classlib/ExecImportCallStmt.h"

namespace pss {

class ExecStmtListImp;
class ExecStmtList {
public:

	ExecStmtList();

	ExecStmtList(const ExecStmtList &rhs);

#ifdef PSS_HAVE_CXX_11
	ExecStmtList(std::initializer_list<ExecStmt> l) : ExecStmtList() {
		ExecStmtList &el = *this;

		for (std::initializer_list<ExecStmt>::const_iterator it=l.begin();
				it!=l.end(); it++) {
			el = (el, *it);
		}
	}

	template <typename T, typename... R> static ExecStmtList mklist(
			const T			&item,
			const R&...		rest) {
		ExecStmtList el;
		return _mklist(el, item, rest...);
	}
#endif

	ExecStmtList(const ExecStmt &rhs);

	virtual ~ExecStmtList();

	ExecStmtList operator,(const ExecStmt &rhs);

	ExecStmtListImp *imp() const;

private:
	ExecStmtList(ExecStmtListImp *imp);

#ifdef PSS_HAVE_CXX_11
	template <typename T, typename... R> static ExecStmtList &_mklist(
			ExecStmtList		&el,
			const T				&item,
			const R&...			rest) {
		el = (el, item);

		return _mklist(el, rest...);
	}

	static ExecStmtList &_mklist(ExecStmtList &el) {
		return el;
	}
#endif


private:
	ExecStmtListImp				*m_imp;

};

}




#endif /* INCLUDE_CLASSLIB_EXECSTMTLIST_H_ */
