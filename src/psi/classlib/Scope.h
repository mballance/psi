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
		m_type = &typeid(T);

		// Save the 'this' handle being passed to us
		m_ctxt = p;

		enter();
	}

	// TODO: Should be able to remove this when conversion to Scope & is complete
	Scope(int v); //

	BaseItem *parent() const;

	BaseItem *ctxt() const { return m_ctxt; }

	const char *name() const;

	virtual ~Scope();

private:
	void enter();

	void leave();

private:
	BaseItem					*m_ctxt;
	const std::type_info	*m_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
