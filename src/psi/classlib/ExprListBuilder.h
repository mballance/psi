/*
 * ExprListBuilder.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_
#define SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_
#include <vector>
#include "classlib/SharedPtr.h"
#include "classlib/ExprCore.h"

namespace psi {

class Expr;
class ExprCore;

class ExprListBuilder {
public:
	ExprListBuilder();
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
