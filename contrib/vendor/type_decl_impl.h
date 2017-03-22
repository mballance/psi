/*
 * type_decl_impl.h
 *
 *  Created on: Mar 22, 2017
 *      Author: ballance
 */

#ifndef CONTRIB_VENDOR_TYPE_DECL_IMPL_H_
#define CONTRIB_VENDOR_TYPE_DECL_IMPL_H_

namespace pss {
namespace vendor {

template <class T> class type_decl_impl : public T {
public:

	type_decl_impl() : T((const char *)0) {
		if (!m_type_id) {
			m_valid = true;
			m_type_id = this;
		}

	}

	static T *id() {
		if (!m_type_id) {
			m_type_id = new T("ANONYMOUS"); // anonymous

			// Calling the constructor will set m_valid to true
			// Flip back, since we're not actually valid
			m_valid = false;
		}
		return m_type_id;
	}

	static bool valid() {
		return m_valid;
	}

private:
	static T				*m_type_id;
	static bool				m_valid;

};

template <class T> T *type_decl_impl<T>::m_type_id = 0;
template <class T> bool type_decl_impl<T>::m_valid = false;

}
}


#endif /* CONTRIB_VENDOR_TYPE_DECL_IMPL_H_ */
