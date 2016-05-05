/*
 * IBitType.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IBITTYPE_H_
#define SRC_PROGRAMMATIC_IBITTYPE_H_

#include <stdint.h>
#include "api/IBaseItem.h"

namespace psi_api {

	class IBitType : public IBaseItem {

		public:

			virtual ~IBitType() { }

			virtual uint32_t getMsb() const = 0;

			virtual uint32_t getLsb() const = 0;

	};
}




#endif /* SRC_PROGRAMMATIC_IBITTYPE_H_ */
