/*
 * SharedPtr.h
 *
 *  Created on: Apr 30, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_SHAREDPTR_H_
#define SRC_STATIC_SHAREDPTR_H_
#include "classlib/Types.h"

template <class T> class SharedPtr {

public:

	SharedPtr(T *ptr=nullptr) : m_ptr(ptr), m_count(nullptr) {
		if (m_ptr) {
			m_count = new int();
			*m_count = 1;
		}
	}

	SharedPtr(T *ptr, int *count) : m_ptr(ptr), m_count(count) {
		if (m_count) {
			(*m_count)++;
		}
	}

	SharedPtr(const SharedPtr<T> &p) :
		m_ptr(p.m_ptr), m_count(p.m_count) {

		if (m_count) {
			(*m_count)++;
		}
	}

	~SharedPtr() {
		if (m_ptr) {
			(*m_count)--;
			if (*m_count == 0) {
				delete m_ptr;
				delete m_count;
			}
		}
	}

	T *ptr() const {
		return m_ptr;
	}

	T *operator -> () {
		return m_ptr;
	}

	const T *operator -> () const {
		return m_ptr;
	}

	const T &operator *() const {
		return *m_ptr;
	}

	T &operator *() {
		return *m_ptr;
	}

private:

	T				*m_ptr;
	int				*m_count;

};



#endif /* SRC_STATIC_SHAREDPTR_H_ */
