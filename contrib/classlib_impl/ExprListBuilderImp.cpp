/*
 * ExprListBuilder.cpp
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
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "ExprListBuilderImp.h"
#include "classlib/ExprListBuilder.h"
#include "classlib/Expr.h"
#include <stdio.h>
#include "ExprCore.h"

namespace pss {

ExprListBuilder::ExprListBuilder() : m_imp(new ExprListBuilderImp()) {
}

ExprListBuilderImp::ExprListBuilderImp() {

}

ExprListBuilder::ExprListBuilder(const std::vector<Expr> &l) :
		m_imp(new ExprListBuilderImp(l)) {

}

ExprListBuilderImp::ExprListBuilderImp(const std::vector<Expr> &l) {
	for (std::vector<Expr>::const_iterator it=l.begin(); it!=l.end(); it++) {
		m_list.push_back((*it).imp());
	}
}

ExprListBuilder::ExprListBuilder(const Expr &e1, const Expr &e2) :
	m_imp(new ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const Expr &e1, const Expr &e2) {
	m_list.push_back(e1.imp());
	m_list.push_back(e2.imp());
}

ExprListBuilder::ExprListBuilder(const Expr &e1, const ExprListBuilder &e2) :
	m_imp(new ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const Expr &e1, const ExprListBuilder &e2) {
	ExprListBuilderImp e1_l;
	e1_l.m_list.push_back(e1.imp());
	m_builders.push_back(e1_l);
	m_builders.push_back(e2.imp());
}

ExprListBuilder &ExprListBuilder::operator,(const ExprListBuilder &rhs) {

	// Convert ourselves int a list of builders
	if (m_imp->m_list.size() > 0) {
		// We're a list of expressions.
		// Pack the expressions into an ExprListBuilder
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

ExprListBuilder &ExprListBuilder::operator,(const Expr &rhs) {
	m_imp->m_list.push_back(rhs.imp());
	return *this;
}

ExprListBuilder::~ExprListBuilder() {
	delete m_imp;
}

ExprListBuilderImp::~ExprListBuilderImp() {
	// TODO Auto-generated destructor stub
}


} /* namespace pss */
