/*
 * IPackage.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IPACKAGE_H_
#define SRC_PROGRAMMATIC_IPACKAGE_H_
#include <string>
#include <vector>

#include "INamedItem.h"

namespace psi {

class IAction;
class IStruct;

class IPackage : public virtual INamedItem {

	public:

		virtual ~IPackage() { }

//		virtual const std::vector<IAction *> &getActions() const = 0;

//		virtual IAction *findAction(const std::string &name) const = 0;

//		virtual void addAction(IAction *action) = 0;

//		virtual const std::vector<IStruct *> getStructs() = 0;
//
//		virtual IStruct *findStruct(const std::string &name) = 0;


};


}




#endif /* SRC_PROGRAMMATIC_IPACKAGE_H_ */
