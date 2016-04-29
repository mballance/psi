/*
 * Chandle.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_CHANDLE_H_
#define SRC_STATIC_CHANDLE_H_
#include "Type.h"

namespace psi {

class Chandle : public Type {

	public:

		Chandle(const std::string &name, IConstructorContext *p);

		virtual ~Chandle();
};

} /* namespace psi */

#endif /* SRC_STATIC_CHANDLE_H_ */
