/*
 * type_decl.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 */

#ifndef INCLUDED_TYPE_DECL_H
#define INCLUDED_TYPE_DECL_H
#include <string>
#include <stdio.h>

namespace pss {

template <class T> class type_decl : public T {
public:

	type_decl(BaseItem *namespace_p=0) : T(Scope(this, namespace_p)) {
		if (!m_type_id) {
			m_valid = true;
			m_type_id = this;
		}
	}

	static T *type_id() {

		if (!m_type_id) {
			m_type_id = new T(true); // anonymous
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

	static T *idOrPrimitive() {
		return (valid())?id():(new T(Scope(true)));
	}

	static bool valid() {
		return m_valid;
	}

private:
	static T 			*m_type_id;
	static bool			m_valid;

};

template <class T> T *type_decl<T>::m_type_id = 0;
template <class T> bool type_decl<T>::m_valid = false;

}

#endif /* INCLUDED_TYPE_DECL_H */

