/*
 * TypeDecl.h
 *
 */

#ifndef SRC_PSI_CLASSLIB_TYPEDECL_H_
#define SRC_PSI_CLASSLIB_TYPEDECL_H_
#include <string>
#include "classlib/TypeRgy.h"

namespace psi {

template <class T> class TypeDecl : public T {
public:

	TypeDecl(Type *namespace_p=0) :
		T(namespace_p), m_type_id(this) { }

private:
	TypeRgy<T>		m_type_id;

};

}



#endif /* SRC_PSI_CLASSLIB_TYPEDECL_H_ */
