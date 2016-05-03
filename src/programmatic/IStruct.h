/*
 * IStruct.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_ISTRUCT_H_
#define SRC_PROGRAMMATIC_ISTRUCT_H_
#include "INamedItem.h"

namespace psi {

	class IStruct : public virtual INamedItem {

		public:

			virtual ~IStruct() { }


	};

}




#endif /* SRC_PROGRAMMATIC_ISTRUCT_H_ */
