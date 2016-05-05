/*
 * PackageImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_PACKAGEIMPL_H_
#define IMPL_PACKAGEIMPL_H_
#include <vector>
#include "api/IAction.h"
#include "api/IPackage.h"
#include "api/IStruct.h"
#include "NamedScopeItemImpl.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class PackageImpl : public IPackage  {
	public:

		PackageImpl(const std::string &name);

		virtual ~PackageImpl();

		virtual IBaseItem::ItemType getType() const { return IBaseItem::TypePackage; }

		virtual const std::vector<IBaseItem *> &getItems() const {
			return m_children;
		}

		virtual void add(IBaseItem *item) {
			m_children.push_back(item);
		}

		virtual const std::string &getName() const {
			return m_name;
		}

		// TODO: Move to Component
		virtual const std::vector<IAction *> getActions();

		virtual IAction *findAction(const std::string &name);

		virtual void addAction(IAction *action);

		virtual const std::vector<IStruct *> getStructs();

		virtual IStruct *findStruct(const std::string &name);

	private:
		std::string							m_name;
		std::vector<IBaseItem *>			m_children;
		std::vector<IAction *>				m_actions;
		std::vector<IStruct *>				m_structs;


};

} /* namespace psi */

#endif /* IMPL_PACKAGEIMPL_H_ */
