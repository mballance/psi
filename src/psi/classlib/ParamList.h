/*
 * ParamList.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_PARAMLIST_H_
#define SRC_STATIC_PARAMLIST_H_

namespace psi {

class Param;
class Type;
class Expr;
class ParamList {

	public:

		ParamList();

		ParamList(const Param &p1, const Param &p2);

		ParamList(const Type &p);

		ParamList(const Expr &p);

		ParamList(int v);

		virtual ~ParamList();

		ParamList operator,(const Param &lhs);

		ParamList operator,(const Type &lhs);
};

} /* namespace psi */

#endif /* SRC_STATIC_PARAMLIST_H_ */
