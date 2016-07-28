/*
 * Scope.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_H
#define INCLUDED_SCOPE_H

#include <string>
#include <vector>
#include <typeinfo>

namespace psi {

class BaseItemImp;
class ScopeImp;
class Scope {
public:
	template <class T> Scope(T *p) {
		// Save the type of the super-class
		init(&typeid(T), p);
	}

	template <class T> Scope(T *t, BaseItem *p) {
		// Save the type of the super-class
		init(&typeid(T), p);
	}

	Scope(bool in_field_decl);

	Scope(const char *name);

	Scope(const std::string &name);

	virtual ~Scope();

	ScopeImp *impl() const;

private:

	void init(const std::type_info *type, BaseItem *ctxt);

private:
	ScopeImp				*m_impl;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
