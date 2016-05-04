/*
 * BaseItemImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_BASEITEMIMPL_H_
#define IMPL_BASEITEMIMPL_H_
#include "api/IBaseItem.h"

namespace psi {

	class BaseItemImpl /*: public virtual IBaseItem*/ {
		public:

			BaseItemImpl(IBaseItem::ItemType t);

			virtual ~BaseItemImpl();

			virtual IBaseItem::ItemType getType() const;

		private:
			IBaseItem::ItemType				m_type;
};

} /* namespace psi */

#endif /* IMPL_BASEITEMIMPL_H_ */
