/*
 * ExprCore.h
 *
 *  Created on: Apr 27, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXPRCORE_H_
#define SRC_STATIC_EXPRCORE_H_
#include "Type.h"
#include "Expr.h"

namespace psi {

class ExprCore {
	public:
		friend class Expr;

		ExprCore(uint32_t v);

		ExprCore(int32_t v);

		ExprCore(const Type &t);

		ExprCore(Expr::Operator op, const Expr &lhs, const Expr &rhs);

		virtual ~ExprCore();

		private:

			union {
				uint64_t			ull;
				int64_t				ll;
				uint32_t			ui;
				int32_t				i;
				const Type			*ref;
			} 						m_val;

			Expr::Operator			m_op;

			Expr					m_lhs;
			Expr					m_rhs;

};

} /* namespace psi */

#endif /* SRC_STATIC_EXPRCORE_H_ */
