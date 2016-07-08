/*
 * Scope.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_SCOPE_H_
#define SRC_PSI_CLASSLIB_SCOPE_H_
#include <string>
#include <vector>
#include <typeinfo>
#include "classlib/SharedPtr.h"

namespace psi {

class BaseItem;
class Scope {
public:
	enum ScopeType {
		ScopeType_TypeDecl,        // class S : public Struct
		ScopeType_FieldDecl,       // Field<S>
		ScopeType_TypeRegistration // TypeDecl<S>
	};

public:
	template <class T> Scope(T *p) {
		m_scope_type = ScopeType_TypeDecl;

		// Save the type of the super-class
		m_type = &typeid(T);

		// Save the 'this' handle being passed to us
		m_ctxt = p;

		enter();
	}

	Scope(ScopeType t); //

	virtual ~Scope();

	BaseItem *parent() const;

	BaseItem *ctxt() const { return m_ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	ScopeType getType() const { return m_scope_type; }

	const char *name() const;

private:
	void enter();

	void leave();

private:
	ScopeType				m_scope_type;
	BaseItem				*m_ctxt;
	const std::type_info	*m_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
