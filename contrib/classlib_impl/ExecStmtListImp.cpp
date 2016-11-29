/*
 * ExecStmtListImp.cpp
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
