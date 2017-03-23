/*
 * expr_list_builder.cpp
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
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "ExprListBuilderImp.h"
#include "classlib/expr_list_builder.h"
#include <stdio.h>

#include "../../include/prv/expr.h"
#include "ExprCore.h"

namespace pss {

expr_list_builder::expr_list_builder() : m_imp(new ExprListBuilderImp()) {
}

ExprListBuilderImp::ExprListBuilderImp() {

}

expr_list_builder::expr_list_builder(const std::vector<expr> &l) :
		m_imp(new ExprListBuilderImp(l)) {

}

ExprListBuilderImp::ExprListBuilderImp(const std::vector<expr> &l) {
	for (std::vector<expr>::const_iterator it=l.begin(); it!=l.end(); it++) {
		m_list.push_back((*it).imp());
	}
}

expr_list_builder::expr_list_builder(const expr &e1, const expr &e2) :
	m_imp(new ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const expr &e1, const expr &e2) {
	m_list.push_back(e1.imp());
	m_list.push_back(e2.imp());
}

expr_list_builder::expr_list_builder(const expr &e1, const expr_list_builder &e2) :
	m_imp(new ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const expr &e1, const expr_list_builder &e2) {
	ExprListBuilderImp e1_l;
	e1_l.m_list.push_back(e1.imp());
	m_builders.push_back(e1_l);
	m_builders.push_back(e2.imp());
}

expr_list_builder &expr_list_builder::operator,(const expr_list_builder &rhs) {

	// Convert ourselves int a list of builders
	if (m_imp->m_list.size() > 0) {
		// We're a list of expressions.
		// Pack the expressions into an expr_list_builder
		ExprListBuilderImp this_l;
		for (std::vector<ExprImp>::const_iterator it=m_imp->m_list.begin();
				it!=m_imp->m_list.end(); it++) {
			this_l.m_list.push_back(*it);
		}
		m_imp->m_builders.push_back(this_l);
		m_imp->m_list.clear();
	}

	// Push the new builder on
	m_imp->m_builders.push_back(rhs.imp());

	return *this;
}

void expr_list_builder::add(const expr &rhs) {
	m_imp->m_list.push_back(rhs.imp());
}

void expr_list_builder::add(const expr_list_builder &rhs) {

	// Convert ourselves int a list of builders
	if (m_imp->m_list.size() > 0) {
		// We're a list of expressions.
		// Pack the expressions into an expr_list_builder
		ExprListBuilderImp this_l;
		for (std::vector<ExprImp>::const_iterator it=m_imp->m_list.begin();
				it!=m_imp->m_list.end(); it++) {
			this_l.m_list.push_back(*it);
		}
		m_imp->m_builders.push_back(this_l);
		m_imp->m_list.clear();
	}

	// Push the new builder on
	m_imp->m_builders.push_back(rhs.imp());
}

expr_list_builder &expr_list_builder::operator,(const expr &rhs) {
	m_imp->m_list.push_back(rhs.imp());
	return *this;
}

expr_list_builder::~expr_list_builder() {
	delete m_imp;
}

ExprListBuilderImp::~ExprListBuilderImp() {
	// TODO Auto-generated destructor stub
}


} /* namespace pss */
