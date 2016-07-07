/*
 * TypeDecl.h
 *
 */

#ifndef SRC_PSI_CLASSLIB_TYPEDECL_H_
#define SRC_PSI_CLASSLIB_TYPEDECL_H_
#include <string>

#include "classlib/Model.h"

namespace psi {

template <class T> class TypeDecl : public T {
public:

	TypeDecl(BaseItem *namespace_p=0) : T(namespace_p, "") {
		fprintf(stdout, "TypeDecl: %s\n",
				static_cast<BaseItem *>(this)->getName().c_str());
		if (!m_type_id) {
			m_valid = true;
			m_type_id = this;
			// TODO: set name based on current scope
		}
	}

	static T *type_id() {

		if (!m_type_id) {
			m_type_id = new T(0, ""); // anonymous
			// TODO: need to demangle name
			fprintf(stdout, "Error: Object %s is missing type registration\n",
					typeid(T).name());

			// Calling the constructor will set m_valid=true.
			// Flip back, since we aren't actually valid
			m_valid = false;

			// Note that this will result in a non-null (but incorrect)
			// result being returned
		}
		return m_type_id;
	}

	static T *id() { return type_id(); }

	static bool valid() {
		return m_valid;
	}

private:
	static T 			*m_type_id;
	static bool			m_valid;

};

template <class T> T *TypeDecl<T>::m_type_id = 0;
template <class T> bool TypeDecl<T>::m_valid = false;

}



#endif /* SRC_PSI_CLASSLIB_TYPEDECL_H_ */
