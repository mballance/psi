/*
 * Int.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INT_H_
#define INT_H_
#include "IntType.h"

namespace psi {

template <int MSB=31, int LSB=0> class Int : public IntType {

	public:

		Int(const std::string &name, Type *p=nullptr) :
			IntType(name, p, MSB, LSB) { }

};

}



#endif /* INT_H_ */
