/*
 * ExprListBuilder.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "classlib/ExprListBuilder.h"
#include "classlib/Expr.h"
#include <stdio.h>
#include "ExprCore.h"

namespace psi {

ExprListBuilder::ExprListBuilder() : m_imp(ExprListBuilderImp()) {
}

ExprListBuilderImp::ExprListBuilderImp() {

}

ExprListBuilder::ExprListBuilder(const Expr &e1, const Expr &e2) :
	m_imp(ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const Expr &e1, const Expr &e2) {
	m_list.push_back(e1.imp());
	m_list.push_back(e2.imp());
}

ExprListBuilder::ExprListBuilder(const Expr &e1, const ExprListBuilder &e2) :
	m_imp(ExprListBuilderImp(e1, e2)) {
}

ExprListBuilderImp::ExprListBuilderImp(const Expr &e1, const ExprListBuilder &e2) {
	ExprListBuilderImp e1_l;
	e1_l.m_list.push_back(e1.imp());
	m_builders.push_back(e1_l);
	m_builders.push_back(e2.imp());
}

ExprListBuilder &ExprListBuilder::operator,(const ExprListBuilder &rhs) {

	// Convert ourselves int a list of builders
	if (m_imp.m_list.size() > 0) {
		// We're a list of expressions.
		// Pack the expressions into an ExprListBuilder
		ExprListBuilderImp this_l;
		for (std::vector<ExprImp>::const_iterator it=m_imp.m_list.begin();
				it!=m_imp.m_list.end(); it++) {
			this_l.m_list.push_back(*it);
		}
		m_imp.m_builders.push_back(this_l);
		m_imp.m_list.clear();
	}

	// Push the new builder on
	m_imp.m_builders.push_back(rhs.imp());

	return *this;
}

ExprListBuilder &ExprListBuilder::operator,(const Expr &rhs) {
	m_imp.m_list.push_back(rhs.imp());
	return *this;
}

ExprListBuilder::~ExprListBuilder() {
	// TODO Auto-generated destructor stub
}

ExprListBuilderImp::~ExprListBuilderImp() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
