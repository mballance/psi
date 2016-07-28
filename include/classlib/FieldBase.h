
#ifndef INCLUDED_FIELD_BASE_H
#define INCLUDED_FIELD_BASE_H
#include "classlib/FieldItem.h"
#include "classlib/TypeDecl.h"

namespace psi {

template <class T> class FieldBase : public T {
public:

	virtual ~FieldBase() { }

	/*
	 * Provide an explicit conversion function to tell the
	 * compiler how to interpret the fact that both we and T extend
	 * from BaseItem
	 */
	operator Expr() const { return Expr(m_field); }

	operator const FieldItem &() const { return m_field; }

protected:

	FieldBase(FieldItem::FieldAttr attr, BaseItem *p, const std::string &name) :
		T(Scope(true)), m_field(p, name, attr) {
		T *t = static_cast<T *>(this);

		// Get the 'authoratative' type declaration from
		// TypeDecl<> in the case of a user-defined type. Otherwise,
		// just set the type handle
		if (TypeDecl<T>::valid()) {
			m_field.setDataType(TypeDecl<T>::id());
		} else {
			m_field.setDataType(t);
		}

		// Propagate parent/child relationships to the 'type' object
		t->setParent(p);
	}


protected:
	FieldItem						m_field;

};

}

#endif /* INCLUDED_FIELD_BASE_H */

