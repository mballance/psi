/*
 * IObjectType.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_IOBJECTTYPE_H_
#define SRC_STATIC_IOBJECTTYPE_H_

namespace psi {

	class IObjectType {
		public:
			enum ObjectType {
				Global,
				Action,
				Component,
				Struct,
				MemoryStruct,
				ResourceStruct,
				StreamStruct,
				Package,
				Type,
				Extend
			};

		public:

			virtual ~IObjectType() { };

			virtual ObjectType getObjectType() = 0;

			static const char *toString(ObjectType t);

			static bool isStruct(ObjectType t);

	};
}




#endif /* SRC_STATIC_IOBJECTTYPE_H_ */
