/*
 * ExprListBuilder.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_
#define SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_
#include <vector>

#include "../../contrib/classlib_impl/ExprCore.h"
#include "classlib/Types.h"
#include "classlib/SharedPtr.h"

namespace psi {

class Expr;
class ExprCore;

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

	const std::vector<SharedPtr<ExprCore> > &getList() const { return m_list; }
	const std::vector<ExprListBuilder> &getBuilderList() const { return m_builders; }

private:
	std::vector<SharedPtr<ExprCore> >			m_list;
	std::vector<ExprListBuilder>				m_builders;

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
