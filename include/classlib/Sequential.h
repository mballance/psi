/*
 * Sequential.h
 *
 *  Created on: Jun 20, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SEQUENTIAL_H
#define INCLUDED_SEQUENTIAL_H
#include "classlib/Types.h"
#include "classlib/ExprList.h"
#include "classlib/ExprListBuilder.h"

namespace psi {

class Sequential : public ExprList {
public:

	Sequential(const ExprListBuilder &body);

#ifdef PSI_HAVE_CXX_11
	Sequential(std::initializer_list<Expr> l) : Sequential(ExprListBuilder(l)) { }
#endif

	virtual ~Sequential();

	ExprListBuilder operator,(const Expr &rhs);

	ExprListBuilder operator,(const ExprListBuilder &rhs);

};

} /* namespace psi */

#endif /* INCLUDED_SEQUENTIAL_H */
