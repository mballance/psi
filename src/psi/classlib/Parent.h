/*
 * Parent.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_PARENT_H_
#define SRC_PSI_CLASSLIB_PARENT_H_
#include <string>
#include <vector>
#include <typeinfo>
#include "classlib/SharedPtr.h"

namespace psi {

class Type;
class Parent {
public:
	template <class T> Parent(T *p) {
		// Save the type of the super-class
		m_type = &typeid(T);

		// Save the 'this' handle being passed to us
		m_ctxt = p;

		enter();
	}

	// TODO: Should be able to remove this when conversion to Parent & is complete
	Parent(int v); //

	Type *parent() const;

	Type *ctxt() const { return m_ctxt; }

	const char *name() const;

	virtual ~Parent();

private:
	void enter();

	void leave();

private:
	Type					*m_ctxt;
	const std::type_info	*m_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_PARENT_H_ */
