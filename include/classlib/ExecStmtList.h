/*
 * ExecStmtList.h
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
