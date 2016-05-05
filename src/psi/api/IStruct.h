/*
 * IStruct.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_ISTRUCT_H_
#define SRC_PROGRAMMATIC_ISTRUCT_H_
#include <string>
#include <vector>

#include "api/IBaseItem.h"

namespace psi_api {

	class IStruct : public IBaseItem {
	public:

		enum StructType {
			Base,
			Memory,
			Stream,
			Resource
		};

		public:

			virtual ~IStruct() { }

			virtual const std::string &getName() const = 0;

			virtual const std::vector<IBaseItem *> &getItems() const = 0;

			virtual void add(IBaseItem *it) = 0;

			virtual StructType getStructType() const = 0;

	};
}




#endif /* SRC_PROGRAMMATIC_ISTRUCT_H_ */
