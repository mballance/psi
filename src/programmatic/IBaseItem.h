/*
 * IBaseItem.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IBASEITEM_H_
#define SRC_PROGRAMMATIC_IBASEITEM_H_

namespace psi {

	class IBaseItem {

	public:

		enum ItemType {
			TypeModel,
			TypeAction,
			TypePackage,
			TypeBit,
			TypeInt
		};

		public:
			virtual ~IBaseItem() { }

			virtual ItemType getType() = 0;

	};


}




#endif /* SRC_PROGRAMMATIC_IBASEITEM_H_ */
