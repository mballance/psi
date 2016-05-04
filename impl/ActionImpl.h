/*
 * ActionImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_ACTIONIMPL_H_
#define IMPL_ACTIONIMPL_H_

#include <string>
#include "api/IAction.h"
#include "NamedItemImpl.h"

namespace psi {

	class ActionImpl: public IAction {

		public:

			ActionImpl(const std::string &name, IAction *super_type);

			virtual ~ActionImpl();

			virtual IBaseItem::ItemType getType() const {
				return IBaseItem::TypeAction;
			}

			virtual const std::string &getName() const;

			virtual const std::vector<IBaseItem *> &getItems() const;

			virtual void add(IBaseItem *);


		private:
			std::string					m_name;
			IAction						*m_super_type;
			std::vector<IBaseItem *>	m_children;


};

} /* namespace psi */

#endif /* IMPL_ACTIONIMPL_H_ */
