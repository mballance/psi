/*
 * SharedPtr.h
 *
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 30, 2016
 *      Author: ballance
 */

#ifndef SRC_CLASSLIB_SHAREDPTR_H_
#define SRC_CLASSLIB_SHAREDPTR_H_
#include <stdio.h>
#include "classlib/Types.h"

template <class T> class SharedPtr {

public:

	SharedPtr(T *ptr) : m_ptr(ptr), m_count(0) {
		if (m_ptr) {
			m_count = new int();
			*m_count = 1;
		}
	}

//	SharedPtr(T *ptr, int *count) : m_ptr(ptr), m_count(count) {
//		if (m_count) {
//			(*m_count)++;
//		}
//	}

	SharedPtr(const SharedPtr<T> &p) :
		m_ptr(p.m_ptr), m_count(p.m_count) {

		if (m_count) {
			(*m_count)++;
		}
	}

	virtual ~SharedPtr() {
		if (m_ptr) {
			(*m_count)--;
			if (*m_count == 0) {
				delete m_ptr;
				delete m_count;
			}
		}
	}

	void inc_ref() {
		if (m_ptr) {
			*m_count++;
		}
	}

	void dec_ref() {
		if (m_ptr) {
			(*m_count)--;
			if (*m_count == 0) {
				T *tmp = m_ptr;
				m_ptr = 0;
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



#endif /* SRC_CLASSLIB_SHAREDPTR_H_ */
