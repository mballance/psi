/*
 * Param.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef PARAM_H_
#define PARAM_H_

namespace psi {

class Type;
class Expr;

class Param {
	public:
		Param(const Type &t);

		Param(const Expr &e);

		Param(int v);

		virtual ~Param();

};

} /* namespace psi */

#endif /* PARAM_H_ */
