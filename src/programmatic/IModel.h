/*
 * IModel.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IMODEL_H_
#define SRC_PROGRAMMATIC_IMODEL_H_
#include <vector>
#include <string>
#include "IBaseItem.h"
#include "IScopeItem.h"
#include "IPackage.h"
#include "IAction.h"
#include "IBitType.h"
#include "IIntType.h"

namespace psi {

	class IModel : public virtual IScopeItem {
		public:

			virtual ~IModel() { }

//			virtual const std::vector<IPackage*> &getPackages() = 0;

			virtual IPackage *getGlobalPackage() = 0;

			virtual IPackage *findPackage(const std::string &name, bool create=false) = 0;

			/**
			 * Data Types
			 */

//			virtual IBitType *mkBitType(uint32_t msb=0, uint32_t lsb=0) = 0;
//
//			virtual IIntType *mkIntType(uint32_t msb=31, uint32_t lsb=0) = 0;
//
//			// TODO: String, Bool types
//
//			/**
//			 * Action
//			 */
//			virtual IAction *mkAction(const std::string &name, IAction *super_type) = 0;
	};

}



#endif /* SRC_PROGRAMMATIC_IMODEL_H_ */
