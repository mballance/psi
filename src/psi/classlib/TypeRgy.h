/*
 * TypeRgy.h
 *
 *  Created on: May 12, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_TYPERGY_H_
#define SRC_PSI_CLASSLIB_TYPERGY_H_
#include <string>
#include "classlib/Type.h"

namespace psi {

template <class T> class TypeRgy {

public:
	TypeRgy(const std::string &name, Type *p) {
		if (!m_type_id) {
			m_type_id = static_cast<T *>(p);
		}
	}

	TypeRgy(Type *p) {
		if (!m_type_id) {
			m_type_id = static_cast<T *>(p);
		}
	}

	static T *type_id() {
		if (!m_type_id) {
			fprintf(stdout, "Error: typeid is null\n");
		}
		return m_type_id;
	}

	static T				*m_type_id;

};

template <class T> T *TypeRgy<T>::m_type_id = 0;

}




#endif /* SRC_PSI_CLASSLIB_TYPERGY_H_ */
