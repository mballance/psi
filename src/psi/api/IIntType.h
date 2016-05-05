/*
 * IIntType.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IINTTYPE_H_
#define SRC_PROGRAMMATIC_IINTTYPE_H_

#include "api/IBaseItem.h"

namespace psi_api {

	class IIntType : public IBaseItem {

		public:

			virtual ~IIntType() { }

			virtual uint32_t getMsb() const = 0;

			virtual uint32_t getLsb() const = 0;
	};
}




#endif /* SRC_PROGRAMMATIC_IINTTYPE_H_ */
