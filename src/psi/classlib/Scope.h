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
	template <class T> Scope(T *p) {
		// Save the type of the super-class
		init(&typeid(T), p);

		enter();
	}

	template <class T> Scope(T *t, BaseItem *p) {
		// Save the type of the super-class
		init(&typeid(T), p);

		enter();
	}

	Scope(bool in_field_decl);

	virtual ~Scope();

	BaseItem *parent() const;

	BaseItem *ctxt() const { return m_ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	bool in_field_decl() const { return m_in_field_decl; }

private:

	void init(const std::type_info *type, BaseItem *ctxt);

	void enter();

	void leave();

private:
	bool					m_in_field_decl;
	BaseItem				*m_ctxt;
	const std::type_info	*m_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
