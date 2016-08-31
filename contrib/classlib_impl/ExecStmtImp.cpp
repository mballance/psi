/*
 * ExecStmtImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecStmtImp.h"

namespace pss {

ExecStmtImp::ExecStmtImp(StmtType type) : m_refcnt(0), m_type(type) { }

ExecStmt::ExecStmt(const ExecStmt &rhs) {
	m_imp = rhs.m_imp;
	m_imp->inc_refcnt();
}

ExecStmt::ExecStmt(ExecStmtImp *imp) {
	m_imp = imp;
	m_imp->inc_refcnt();
}

ExecStmt::~ExecStmt() {
	m_imp->dec_refcnt();
}

ExecStmtImp *ExecStmt::imp() const {
	return m_imp;
}

ExecStmtImp::~ExecStmtImp() {
	// TODO Auto-generated destructor stub
}

void ExecStmtImp::inc_refcnt() {
	m_refcnt++;
}

void ExecStmtImp::dec_refcnt() {
	m_refcnt--;

	if (m_refcnt == 0) {
		delete this;
	}
}

} /* namespace pss */
