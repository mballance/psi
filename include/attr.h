/*
 * attr.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_ATTR_H
#define INCLUDED_ATTR_H

#include <string>

//<vendor>
#include "attr_impl.h"
//</vendor>
#include "prv/attr_item.h"
#include "pss_bit.h"
#include "pss_int.h"
#include "prv/expr.h"

namespace pss {

using namespace prv;

#define ATTR_OP_METHODS(_op) \
	expr operator _op (unsigned int v); \
	expr operator _op (int v); \
	expr operator _op (const attr_item &rhs); \
	expr operator _op (const expr &rhs);


#define ATTR_OPERATORS \
	ATTR_OP_METHODS(==) \
	ATTR_OP_METHODS(!=) \
	ATTR_OP_METHODS(<=) \
	ATTR_OP_METHODS(<) \
	ATTR_OP_METHODS(>=) \
	ATTR_OP_METHODS(>) \
	ATTR_OP_METHODS(&) \
	ATTR_OP_METHODS(&&) \
	ATTR_OP_METHODS(|) \
	ATTR_OP_METHODS(||) \
	ATTR_OP_METHODS(-) \
	ATTR_OP_METHODS(+) \
	ATTR_OP_METHODS(*) \
	ATTR_OP_METHODS(/) \
	ATTR_OP_METHODS(%) 

template <class T> class attr : public vendor::attr_impl<T> {
	public:

		attr(const scope &name);

#ifdef UNDEFINED
//		attr(base_item *p, const std::string &name) :
//			attr_base<T>(vendor::attr_item_impl::AttrNone, p, name) { }
//
//		attr(base_item *p, const std::string &name, const expr &array_dim) :
//			attr_base<T>(vendor::attr_item_impl::AttrNone, p, name, array_dim) { }
#endif /* UNDEFINED */

		virtual ~attr();

#ifdef UNDEFINED
		exec_stmt operator =(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field = rhs); }

		exec_stmt operator =(const expr &rhs) { return (attr_base<T>::m_field = rhs); }

		exec_stmt operator +=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field += rhs); }

		exec_stmt operator +=(const expr &rhs) { return (attr_base<T>::m_field += rhs); }

		exec_stmt operator -=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field -= rhs); }

		exec_stmt operator -=(const expr &rhs) { return (attr_base<T>::m_field -= rhs); }

		exec_stmt operator <<=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field <<= rhs); }

		exec_stmt operator <<=(const expr &rhs) { return (attr_base<T>::m_field <<= rhs); }

		exec_stmt operator >>=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field >>= rhs); }

		exec_stmt operator >>=(const expr &rhs) { return (attr_base<T>::m_field >>= rhs); }

		exec_stmt operator |=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field |= rhs); }

		exec_stmt operator |=(const expr &rhs) { return (attr_base<T>::m_field |= rhs); }

		exec_stmt operator &=(const exec_import_call_stmt &rhs) { return (attr_base<T>::m_field &= rhs); }

		exec_stmt operator &=(const expr &rhs) { return (attr_base<T>::m_field &= rhs); }
#endif

};

template <> class attr<pss_int> : public attr_item {
public:

	attr(const scope &name);

	attr(const scope &name, const pss_int &t_decl);

	void set(int64_t v);

	int64_t get();

	ATTR_OPERATORS
};

#ifdef UNDEFINED
template <> class attr<pss_bit> : public vendor::attr_item_impl {
public:
	attr(const scope &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_bit(), 0) { }

	attr(const scope &name, const pss_bit &t_decl) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, t_decl, 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }

	ATTR_OPERATORS

};

template <> class attr<unsigned long long> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_bit(64), 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }

	ATTR_OPERATORS
};

template <> class attr<long long> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_int(64), 0) { }

	void set(int64_t v) { set_int(v); }

	int64_t get() { return get_int(); }

	ATTR_OPERATORS

};
#endif /* UNDEFINED */

template <> class attr<unsigned int> : public vendor::attr_item_impl {
public:

	attr(const std::string &name);

	void set(uint32_t v);

	uint32_t get();

	ATTR_OPERATORS
};

template <> class attr<int> : public vendor::attr_item_impl {
public:

	attr(const std::string &name);

	void set(int32_t v);

	int32_t get();

	ATTR_OPERATORS

};

#ifdef UNDEFINED
template <> class attr<unsigned short> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_bit(16), 0) { }

	void set(uint16_t v) { set_bit(v); }

	uint16_t get() { return get_bit(); }

	ATTR_OPERATORS
};

template <> class attr<short> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_int(16), 0) { }

	void set(int16_t v) { set_int(v); }

	int16_t get() { return get_int(); }

	ATTR_OPERATORS

};

template <> class attr<unsigned char> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_bit(8), 0) { }

	void set(uint8_t v) { set_bit(v); }

	uint8_t get() { return get_bit(); }

	ATTR_OPERATORS
};

template <> class attr<char> : public vendor::attr_item_impl {
public:

	attr(const std::string &name) :
		vendor::attr_item_impl(this, vendor::attr_item_impl::AttrNone, pss_int(8), 0) { }

	void set(int8_t v) { set_int(v); }

	int8_t get() { return get_int(); }

	ATTR_OPERATORS
};

template <> class attr<bool> : public vendor::attr_item_impl {
public:
	attr(const scope &name) :
		vendor::attr_item_impl(name, vendor::attr_item_impl::AttrNone, pss_bool(), 0) { }

	void set(bool v) { set_bit(v); }

	bool get() { return get_bit(); }

	ATTR_OPERATORS
};
#endif /* UNDEFINED */

#undef ATTR_OP_METHODS
#undef ATTR_OPERATORS

}

//<vendor>
#include "attr.hpp"
//</vendor>


#endif /* INCLUDED_ATTR_H */
