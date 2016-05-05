/*
 * NamedItemImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_NAMEDITEMIMPL_H_
#define IMPL_NAMEDITEMIMPL_H_
#include <string>
#include "api/INamedItem.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class NamedItemImpl : public virtual INamedItem, public BaseItemImpl {
	public:

		NamedItemImpl(const std::string &name, IBaseItem::ItemType t);

		virtual ~NamedItemImpl();

		virtual const std::string &getName();

	private:

		std::string					m_name;
};

} /* namespace psi */

#endif /* IMPL_NAMEDITEMIMPL_H_ */
