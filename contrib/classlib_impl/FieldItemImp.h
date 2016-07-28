/*
 * FieldItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FIELD_ITEM_IMP_H
#define INCLUDED_FIELD_ITEM_IMP_H
#include <string>
#include "classlib/FieldItem.h"
#include "NamedBaseItemImp.h"

namespace psi {

class FieldItemImp: public NamedBaseItemImp {
public:
	FieldItemImp(
			FieldItem 				*master,
			BaseItem 				*p,
			const std::string 		&name,
			FieldItem::FieldAttr	attr);

	virtual ~FieldItemImp();

	BaseItem *getDataType() const { return m_data_type; }

	void setDataType(BaseItem *dt) { m_data_type = dt; }

	FieldItem::FieldAttr getAttr() const { return m_attr; }

	void setAttr(FieldItem::FieldAttr attr) { m_attr = attr; }

	void setInternal(bool i) { m_internal = i; }

	bool isInternal() const { return m_internal; }

private:
	BaseItem				*m_data_type;
	FieldItem::FieldAttr	m_attr;
	bool					m_internal;

};

} /* namespace psi */

#endif /* INCLUDED_FIELD_ITEM_H */
