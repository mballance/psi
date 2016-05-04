/*
 * IComponent.h
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICOMPONENT_H_
#define SRC_PSI_API_ICOMPONENT_H_
#include <string>
#include <vector>

#include "IBaseItem.h"

namespace psi {

class IComponent: public IBaseItem {
	public:

		virtual ~IComponent() { };

		virtual const std::string &getName() const = 0;

		virtual const std::vector<IBaseItem *> &getItems() const = 0;

		virtual void add(IBaseItem *it) = 0;
};

} /* namespace psi */

#endif /* SRC_PSI_API_ICOMPONENT_H_ */
