/*
 * IType.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_ITYPE_H_
#define SRC_PROGRAMMATIC_ITYPE_H_

namespace psi {

	class IType {
		public:
			enum DataType {
				Bit,
				Int,
				String,
				Bool,
				Action,
				Struct
			};

		public:

			virtual ~IType() { }

			virtual DataType getDataType() = 0;


	};
}



#endif /* SRC_PROGRAMMATIC_ITYPE_H_ */
