/*
 * constraint_stmt.h
 *
 *  Created on: Mar 23, 2017
 *      Author: ballance
 */

#ifndef INCLUDE_CONSTRAINT_STMT_H_
#define INCLUDE_CONSTRAINT_STMT_H_
#include "prv/expr.h"

namespace pss {
class pss_if;

namespace prv {

class constraint_stmt : public vendor::constraint_stmt_impl {
public:
	//<vendor>
	using vendor::constraint_stmt_impl::constraint_stmt_impl;
	//</vendor>

	constraint_stmt(const expr &expr);

	constraint_stmt(const pss_if &if_stmt);

};

} /* namespace prv */
} /* namespace pss */




#endif /* INCLUDE_CONSTRAINT_STMT_H_ */
