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

#include "attr.h"
#ifdef UNDEFINED
#include "pss_int.h"
#include "pss_bit.h"
#include "classlib/pss_bool.h"
#include "prv/expr.h"
#endif

namespace pss {

#define ATTR_OP_METHODS(_op) \
	expr operator _op (unsigned int v); \
	expr operator _op (int v); \
	expr operator _op (const attr_item &rhs); \
	expr operator _op (const expr &rhs); \

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

template <class T> class rand_attr : public vendor::rand_attr_impl<T> {

	public:
		rand_attr(const scope &name);

		virtual ~rand_attr() { };

};


template <> class rand_attr<pss_bit> : public attr_item {
public:
	rand_attr(const scope &name);

	rand_attr(const scope &name, const pss_bit &t_decl);

	rand_attr(const scope &name, uint32_t w);

	void set(uint64_t v);

	uint64_t get();

	ATTR_OPERATORS

};

template <> class rand_attr<pss_int> : public attr_item {
public:
	rand_attr(const scope &name);

	rand_attr(const scope &name, const pss_int &t_decl);

	rand_attr(const scope &name, uint32_t w);

	void set(int64_t v);

	int64_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<unsigned long long> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(uint64_t v);

	uint64_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<long long> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(int64_t v);

	int64_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<unsigned int> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(uint32_t v);

	uint32_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<int> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(int32_t v);

	int32_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<unsigned short> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(uint16_t v);

	uint16_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<short> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(int16_t v);

	int16_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<unsigned char> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(uint8_t v);

	uint8_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<char> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(int8_t v);

	int8_t get();

	ATTR_OPERATORS
};

template <> class rand_attr<bool> : public attr_item {
public:
	rand_attr(const scope &name);

	void set(bool v);

	bool get();

	ATTR_OPERATORS
};

#undef ATTR_OP_METHODS
#undef ATTR_OPERATORS

} /* namespace pss */

#endif /* INCLUDED_RAND_H */
