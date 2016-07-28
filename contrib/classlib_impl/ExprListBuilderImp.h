/*
 * ExprListBuilder.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_BUILDER_IMP_H
#define INCLUDED_EXPR_LIST_BUILDER_IMP_H
#include <vector>

#include "classlib/ExprListBuilder.h"
#include "ExprImp.h"

namespace psi {

class Expr;
class ExprImp;
class ExprListBuilderImp {
public:
	friend class ExprListBuilder;

	ExprListBuilderImp();

#ifdef PSI_HAVE_CXX_11
	ExprListBuilder(std::initializer_list<Expr> l) : ExprListBuilder() {
		std::initializer_list<Expr>::const_iterator it;

		for (it=l.begin(); it!=l.end(); it++) {
			m_list.push_back((*it).getCore());
		}
	}
#endif

	ExprListBuilderImp(const Expr &e1, const Expr &e2);

	ExprListBuilderImp(const Expr &e1, const ExprListBuilder &e2);

	virtual ~ExprListBuilderImp();

	const std::vector<ExprImp>            &getList() const { return m_list; }
	const std::vector<ExprListBuilderImp> &getBuilderList() const { return m_builders; }

private:
	std::vector<ExprImp>					m_list;
	std::vector<ExprListBuilderImp>			m_builders;

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
