/*
 * TypeRgy.h
 *
 *  Created on: May 12, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_TYPERGY_H_
#define SRC_PSI_CLASSLIB_TYPERGY_H_
#include <string>
#include "classlib/BaseItem.h"

namespace psi {

template <class T> class TypeRgy {

public:
	TypeRgy(const std::string &name, T *p) {
		if (!m_type_id) {
			m_type_id = p;
			m_valid = true;
		}
	}

	TypeRgy(T *p) {
		if (!m_type_id) {
			m_type_id = p;
		}
	}

	static T *type_id() {
		if (!m_type_id) {
			m_type_id = new T(0);
			fprintf(stdout, "Error: Object %s is missing type registration\n",
					m_type_id->getName().c_str());
			// Calling the constructor will set m_valid=true.
			// Flip back, since we aren't actually valid
			m_valid = false;
			// Note that this will result in a non-null (but incorrect)
			// result being returned
		}
		return m_type_id;
	}

	static bool valid() {
		return m_valid;
	}

	static T				*m_type_id;
	static bool				m_valid;

};

template <class T> T *TypeRgy<T>::m_type_id = 0;
template <class T> bool TypeRgy<T>::m_valid = false;

}




#endif /* SRC_PSI_CLASSLIB_TYPERGY_H_ */
