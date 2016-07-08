/*
 * FieldItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_FIELDITEM_H_
#define SRC_PSI_CLASSLIB_FIELDITEM_H_
#include <string>
#include "classlib/NamedBaseItem.h"
#include "classlib/Scope.h"

namespace psi {

class FieldItem: public NamedBaseItem {
public:
	enum FieldAttr {
		AttrNone = 0,
		AttrInput,
		AttrOutput,
		AttrLock,
		AttrShare,
		AttrRand,
		AttrPool
	};

public:
	FieldItem(BaseItem *p, const std::string &name);

	virtual ~FieldItem();

	BaseItem *getDataType() const { return m_data_type; }

	void setDataType(BaseItem *dt) { m_data_type = dt; }

	FieldAttr getAttr() const { return m_attr; }

	void setAttr(FieldAttr attr) { m_attr = attr; }

private:
	BaseItem				*m_data_type;
	FieldAttr				m_attr;

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_FIELDITEM_H_ */
