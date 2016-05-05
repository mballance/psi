/*
 * FieldImpl.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef IMPL_FIELDIMPL_H_
#define IMPL_FIELDIMPL_H_
#include "api/IField.h"

using namespace psi_api;

namespace psi {

class FieldImpl: public IField {
public:

	FieldImpl(
			const std::string 	&name,
			IBaseItem 			*field_type,
			IField::FieldAttr 	attr);

	virtual ~FieldImpl();

	virtual IBaseItem::ItemType getType() const { return IBaseItem::TypeField; }

	virtual const std::string &getName() const { return m_name; }

	virtual IBaseItem *getDataType() const { return m_field_type; }

	virtual FieldAttr getAttr() const { return m_attr; }

private:
	std::string					m_name;
	IBaseItem					*m_field_type;
	FieldAttr					m_attr;

};

} /* namespace psi */

#endif /* IMPL_FIELDIMPL_H_ */
