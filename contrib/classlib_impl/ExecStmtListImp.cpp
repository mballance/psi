/*
 * ExecStmtListImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecStmtListImp.h"

namespace pss {

ExecStmtList::ExecStmtList() {
	m_imp = new ExecStmtListImp();
	m_imp->inc_refcnt();
}

ExecStmtList::ExecStmtList(const ExecStmtList &rhs) {
	m_imp = rhs.m_imp;
	m_imp->inc_refcnt();
}

ExecStmtList::ExecStmtList(ExecStmtListImp *imp) {
	m_imp = imp;
	m_imp->inc_refcnt();
}

ExecStmtList::ExecStmtList(const ExecStmt &rhs) {
	m_imp = new ExecStmtListImp();
	m_imp->inc_refcnt();
	m_imp->add(rhs);
}

ExecStmtList::~ExecStmtList() {
	m_imp->dec_refcnt();
}

ExecStmtListImp::ExecStmtListImp() : m_refcnt(0) {
	// TODO Auto-generated constructor stub

}

ExecStmtListImp::~ExecStmtListImp() {
	// TODO Auto-generated destructor stub
}

void ExecStmtListImp::add(const ExecStmt &stmt) {
	m_stmts.push_back(stmt);
}

ExecStmtList ExecStmtList::operator,(const ExecStmt &rhs) {
	m_imp->add(rhs);
	return *this;
}

ExecStmtListImp *ExecStmtList::imp() const {
	return m_imp;
}

void ExecStmtListImp::inc_refcnt() {
	m_refcnt++;
}

void ExecStmtListImp::dec_refcnt() {
	m_refcnt--;

	if (!m_refcnt) {
		delete this;
	}
}

} /* namespace pss */
