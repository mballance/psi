/*
 * ExprListBuilder.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "classlib/ExprListBuilder.h"
#include "classlib/Expr.h"
#include "classlib/ExprCore.h"
#include <stdio.h>

namespace psi {

ExprListBuilder::ExprListBuilder() {
}

ExprListBuilder::ExprListBuilder(const Expr &e1, const Expr &e2) {
	m_list.push_back(e1.getCore());
	m_list.push_back(e2.getCore());
}

ExprListBuilder::ExprListBuilder(const Expr &e1, const ExprListBuilder &e2) {
	ExprListBuilder e1_l;
	e1_l.m_list.push_back(e1.getCore());
	m_builders.push_back(e1_l);
	m_builders.push_back(e2);
}

ExprListBuilder &ExprListBuilder::operator,(const ExprListBuilder &rhs) {
	fprintf(stdout, "ExprListBuilder::operator,(ExprListBuilder)\n");

	// Convert ourselves int a list of builders
	if (m_list.size() > 0) {
		// We're a list of expressions.
		// Pack the expressions into an ExprListBuilder
		ExprListBuilder this_l;
		for (std::vector<SharedPtr<ExprCore> >::const_iterator it=m_list.begin();
				it!=m_list.end(); it++) {
			this_l.m_list.push_back(*it);
		}
		m_builders.push_back(this_l);
		m_list.clear();
	}

	// Push the new builder on
	m_builders.push_back(rhs);

	return *this;
}

ExprListBuilder::~ExprListBuilder() {
	// TODO Auto-generated destructor stub
}

ExprListBuilder &ExprListBuilder::operator,(const Expr &rhs) {
	fprintf(stdout, "ExprListBuilder::operator,(Expr)\n");
	m_list.push_back(rhs.getCore());
	return *this;
}

} /* namespace psi */
