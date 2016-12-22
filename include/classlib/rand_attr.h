/*
 * rand_attr.h
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_RAND_H
#define INCLUDED_RAND_H
#include <string>

#include "classlib/FieldBase.h"
#include "classlib/pss_int.h"
#include "classlib/pss_bit.h"
#include "classlib/pss_bool.h"

namespace pss {

template <class T> class rand_attr : public FieldBase<T> {

	public:
		rand_attr(const Scope &scope) :
			FieldBase<T>(FieldItem::AttrRand, scope) { }

//		rand_attr(BaseItem *p, const std::string &name, const Expr &array_dim) :
//			FieldBase<T>(FieldItem::AttrRand, p, name, array_dim) { }

		virtual ~rand_attr() { };

};


template <> class rand_attr<pss_bit> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(), 0) { }

	rand_attr(const Scope &name, const pss_bit &t_decl) :
		FieldItem(name, FieldItem::AttrRand, t_decl, 0) { }

	rand_attr(const Scope &name, uint32_t w) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(w), 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }

};

template <> class rand_attr<pss_int> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_int(), 0) { }

	rand_attr(const Scope &name, const pss_int &t_decl) :
		FieldItem(name, FieldItem::AttrRand, t_decl, 0) { }

	rand_attr(const Scope &name, uint32_t w) :
		FieldItem(name, FieldItem::AttrRand, pss_int(w), 0) { }

	void set(int64_t v) { set_int(v); }

	int64_t get() { return get_int(); }

};

template <> class rand_attr<unsigned long long> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(32), 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }
};

template <> class rand_attr<long long> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_int(32), 0) { }

	void set(int64_t v) { set_int(v); }

	int64_t get() { return get_int(); }
};

template <> class rand_attr<unsigned int> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(32), 0) { }

	void set(uint32_t v) { set_bit(v); }

	uint32_t get() { return get_bit(); }
};

template <> class rand_attr<int> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_int(32), 0) { }

	void set(int32_t v) { set_int(v); }

	int32_t get() { return get_int(); }
};

template <> class rand_attr<unsigned short> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(16), 0) { }

	void set(uint16_t v) { set_bit(v); }

	uint16_t get() { return get_bit(); }
};

template <> class rand_attr<short> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_int(16), 0) { }

	void set(int16_t v) { set_int(v); }

	int16_t get() { return get_int(); }
};

template <> class rand_attr<unsigned char> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bit(8), 0) { }

	void set(uint8_t v) { set_bit(v); }

	uint8_t get() { return get_bit(); }
};

template <> class rand_attr<char> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_int(8), 0) { }

	void set(int8_t v) { set_int(v); }

	int8_t get() { return get_int(); }
};

template <> class rand_attr<bool> : public FieldItem {
public:
	rand_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrRand, pss_bool(), 0) { }

	void set(bool v) { set_bit(v); }

	bool get() { return get_bit(); }
};

} /* namespace pss */

#endif /* INCLUDED_RAND_H */
