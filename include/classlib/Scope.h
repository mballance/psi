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

namespace psi {

class BaseItemImpl;
class ScopeImpl;
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

	ScopeImpl *impl() const;

private:

	void init(const std::type_info *type, BaseItem *ctxt);

private:
	ScopeImpl				*m_impl;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
