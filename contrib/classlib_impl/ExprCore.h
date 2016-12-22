/*
 * ExprCore.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 *  Created on: Apr 27, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_CORE_H
#define INCLUDED_EXPR_CORE_H
#include "ExprImp.h"
#include "classlib/base_item.h"

namespace pss {

class import_func;
class expr;
class ExprCore {

	public:
		friend class expr;

		ExprCore(uint32_t v);

		ExprCore(int32_t v);

		ExprCore(const base_item &t);

		ExprCore(ExprImp::Operator op, const expr &lhs, const expr &rhs);

		ExprCore(import_func &import, const expr &params);

		ExprCore(ExprImp::Operator op);

		virtual ~ExprCore();

		ExprImp::Operator getOp() const { return m_op; }

		void setOp(ExprImp::Operator op) { m_op = op; }

		ExprCore *getLhsPtr() const { return m_lhs.ptr(); }

		ExprCore *getRhsPtr() const { return m_rhs.ptr(); }

		uint64_t getValUI() { return m_val.ull; }

		int64_t getValI() { return m_val.i; }

		BaseItemImp *getTypePtr() const { return m_val.ref; }

		protected:

			union {
				uint64_t			ull;
				int64_t				ll;
				uint32_t			ui;
				int32_t				i;
				BaseItemImp			*ref;
			} 						m_val;

			ExprImp::Operator		m_op;

			ExprImp					m_lhs;
			ExprImp					m_rhs;

};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXPRCORE_H_ */
