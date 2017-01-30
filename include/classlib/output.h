/*
 * output.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H
#include <string>
#include <stdio.h>

#include "classlib/attr_item.h"
#include "classlib/type_decl.h"

namespace pss {

class action;
template <class T> class output : public T {

	public:
		/**
		 * This constructor is used to specify an action output field
		 */
		output(const scope &scope) : T(static_cast<T *>(this)) {
			attr_item &it = static_cast<attr_item &>(*this);
			it.setModifiers(attr_item::AttrOutput);
		}

		virtual ~output() { }

};

template <> class output<pss_bit> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_bit(), 0) { }

	output(const scope &name, const pss_bit &t_decl) :
		attr_item(name, attr_item::AttrOutput, t_decl, 0) { }

	output(const scope &name, uint32_t w) :
		attr_item(name, attr_item::AttrOutput, pss_bit(w), 0) { }

};

template <> class output<pss_int> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_int(), 0) { }

	output(const scope &name, const pss_int &t_decl) :
		attr_item(name, attr_item::AttrOutput, t_decl, 0) { }

	output(const scope &name, uint32_t w) :
		attr_item(name, attr_item::AttrOutput, pss_int(w), 0) { }

};

template <> class output<unsigned int> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_bit(32), 0) { }

};

template <> class output<int> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_int(32), 0) { }

};

template <> class output<unsigned short> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_bit(16), 0) { }

};

template <> class output<short> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_int(16), 0) { }

};

template <> class output<unsigned char> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_bit(8), 0) { }

};

template <> class output<char> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_int(8), 0) { }

};

template <> class output<bool> : public attr_item {
public:
	output(const scope &name) :
		attr_item(name, attr_item::AttrOutput, pss_bool(), 0) { }

};


} /* namespace pss */

#endif /* INCLUDED_OUTPUT_H */
