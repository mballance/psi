/*
 * IAction.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IACTION_H_
#define SRC_PROGRAMMATIC_IACTION_H_
#include <string>
#include <vector>

#include "api/IBaseItem.h"
#include "api/IScopeItem.h"

namespace psi {
	class IAction : public IBaseItem, public virtual IScopeItem {

		public:

			virtual ~IAction() { };

			virtual const std::string &getName() const = 0;

			virtual const std::vector<IBaseItem *> &getItems() const = 0;

			virtual void add(IBaseItem *it) = 0;

	};

}




#endif /* SRC_PROGRAMMATIC_IACTION_H_ */
