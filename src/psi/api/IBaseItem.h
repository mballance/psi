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
			TypeAction,
			TypeBit,
			TypeBool,
			TypeChandle,
			TypeComponent,
			TypeConstraint,
			TypeImport,
			TypeInt,
			TypeExec,
			TypeExtendAction,
			TypeExtendComponent,
			TypeExtendStruct,
			TypeModel,
			TypePackage,
			TypeString,
			TypeStruct
		};

		public:
			virtual ~IBaseItem() { }

			virtual ItemType getType() const = 0;

	};


}




#endif /* SRC_PROGRAMMATIC_IBASEITEM_H_ */
