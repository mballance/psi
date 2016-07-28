/*
 * ExprListBuilder.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_BUILDER_H
#define INCLUDED_EXPR_LIST_BUILDER_H
#include <vector>

#include "classlib/Types.h"

namespace psi {

class Expr;
class ExprListBuilderImp;
class ExprListBuilder {
public:

	ExprListBuilder();

#ifdef PSI_HAVE_CXX_11
	ExprListBuilder(std::initializer_list<Expr> l) : ExprListBuilder() {
		std::initializer_list<Expr>::const_iterator it;

		for (it=l.begin(); it!=l.end(); it++) {
			m_list.push_back((*it).getCore());
		}
	}
#endif

	ExprListBuilder(const Expr &e1, const Expr &e2);

	ExprListBuilder(const Expr &e1, const ExprListBuilder &e2);

	virtual ~ExprListBuilder();

	ExprListBuilder &operator,(const Expr &rhs);

	ExprListBuilder &operator,(const ExprListBuilder &rhs);

	ExprListBuilderImp &imp() const { return m_imp; }

private:
	ExprListBuilderImp							&m_imp;

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
