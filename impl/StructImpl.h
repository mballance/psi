/*
 * StructImpl.h
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef IMPL_STRUCTIMPL_H_
#define IMPL_STRUCTIMPL_H_
#include <string>
#include <vector>

#include "api/IStruct.h"

using namespace psi_api;

namespace psi {

class StructImpl: public IStruct {
public:

	StructImpl(const std::string &name, psi_api::IStruct::StructType t, IStruct *super_type);

	virtual ~StructImpl();

	virtual IBaseItem::ItemType getType() const {
		return IBaseItem::TypeStruct;
	}

	virtual const std::string &getName() const;

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void add(IBaseItem *it);

	virtual psi_api::IStruct::StructType getStructType() const {
		return m_struct_type;
	}

private:
	std::string						m_name;
	psi_api::IStruct::StructType	m_struct_type;
	std::vector<IBaseItem *>		m_children;
	IStruct							*m_super_type;

};

} /* namespace psi */

#endif /* IMPL_STRUCTIMPL_H_ */
