/*
 * ActionImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_ACTIONIMPL_H_
#define IMPL_ACTIONIMPL_H_

#include <string>
#include "IAction.h"
#include "NamedItemImpl.h"

namespace psi {

	class ActionImpl: public virtual IAction, public NamedItemImpl {

		public:

			ActionImpl(const std::string &name, IAction *super_type);

			virtual ~ActionImpl();

		private:

			IAction					*m_super_type;

};

} /* namespace psi */

#endif /* IMPL_ACTIONIMPL_H_ */
