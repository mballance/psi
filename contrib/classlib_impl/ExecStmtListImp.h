/*
 * ExecStmtListImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECSTMTLISTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECSTMTLISTIMP_H_
#include <vector>
#include "classlib/ExecStmtList.h"

namespace pss {

class ExecStmtListImp {
public:
	ExecStmtListImp();

	virtual ~ExecStmtListImp();

	void add(const ExecStmt &stmt);

	void inc_refcnt();

	void dec_refcnt();

	const std::vector<ExecStmt> &stmts() const { return m_stmts; }

private:
	uint32_t				m_refcnt;
	std::vector<ExecStmt>	m_stmts;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECSTMTLISTIMP_H_ */
