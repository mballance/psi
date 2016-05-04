/*
 * ExprCore.h
 *
 *  Created on: Apr 27, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXPRCORE_H_
#define SRC_STATIC_EXPRCORE_H_
#include "classlib/Expr.h"
#include "classlib/Type.h"

namespace psi {

class ExprCore {

	public:
		friend class Expr;

		ExprCore(uint32_t v);

		ExprCore(int32_t v);

		ExprCore(const Type &t);

		ExprCore(Expr::Operator op, const Expr &lhs, const Expr &rhs);

		ExprCore(Expr::Operator op);

		virtual ~ExprCore();

		Expr::Operator getOp() const { return m_op; }

		ExprCore *getLhsPtr() const { return m_lhs.getCorePtr(); }

		ExprCore *getRhsPtr() const { return m_rhs.getCorePtr(); }

		uint64_t getValUI() { return m_val.ull; }

		int64_t getValI() { return m_val.i; }

		protected:

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
