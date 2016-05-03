/*
 * IIntType.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IINTTYPE_H_
#define SRC_PROGRAMMATIC_IINTTYPE_H_

#include "IType.h"

namespace psi {

	class IIntType : public virtual IType {

		public:

			virtual ~IIntType() { }

			virtual uint32_t getMsb() = 0;

			virtual uint32_t getLsb() = 0;
	};
}




#endif /* SRC_PROGRAMMATIC_IINTTYPE_H_ */
