/*
 * AttributeImpl.h
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_ATTRIBUTEIMPL_H_
#define CONTRIB_CLASSLIB_IMPL_ATTRIBUTEIMPL_H_
#include <string>

namespace psi {

class AttributeImpl {
public:
	enum AttrType {
		AttrType_String,
		AttrType_Bool,
		AttrType_Obj
	};

	AttributeImpl(const std::string &name, const std::string &value);

	AttributeImpl(const std::string &name, bool val);

	AttributeImpl(const std::string &name, void *hndl);

	const std::string &getStrValue() { return *m_val.str; }

	void *getObjValue() { return m_val.hndl; }

	virtual ~AttributeImpl();

	union {
		std::string		*str;
		void			*hndl;
		bool			bval;
	} m_val;
};

} /* namespace psi */

#endif /* CONTRIB_CLASSLIB_IMPL_ATTRIBUTEIMPL_H_ */
