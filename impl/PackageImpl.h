/*
 * PackageImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_PACKAGEIMPL_H_
#define IMPL_PACKAGEIMPL_H_
#include <vector>
#include "IPackage.h"
#include "NamedItemImpl.h"

namespace psi {

class IAction;
class IStruct;

class PackageImpl : public virtual IPackage, public NamedItemImpl {
	public:

		PackageImpl(const std::string &name);

		virtual ~PackageImpl();

		// TODO: Move to Component
		virtual const std::vector<IAction *> getActions();

		virtual IAction *findAction(const std::string &name);

		virtual void addAction(IAction *action);

		virtual const std::vector<IStruct *> getStructs();

		virtual IStruct *findStruct(const std::string &name);

	private:
		std::vector<IAction *>				m_actions;
		std::vector<IStruct *>				m_structs;


};

} /* namespace psi */

#endif /* IMPL_PACKAGEIMPL_H_ */
