/*
 * input.h
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

#ifndef INCLUDED_INPUT_H
#define INCLUDED_INPUT_H
#include <string>

#include "classlib/FieldItem.h"
#include "classlib/type_decl.h"

namespace pss {

class action;
template <class T> class input : public T {

	public:
		/**
		 * This constructor is used for specifying an action input field
		 */
		input(const Scope &name) : T(static_cast<T *>(this)) {
			FieldItem &it = static_cast<FieldItem &>(*this);
			it.setModifiers(FieldItem::AttrInput);
		}

		virtual ~input() { }

};

template <> class input<pss_bit> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_bit(), 0) { }

	input(const Scope &name, const pss_bit &t_decl) :
		FieldItem(name, FieldItem::AttrInput, t_decl, 0) { }

	input(const Scope &name, uint32_t w) :
		FieldItem(name, FieldItem::AttrInput, pss_bit(w), 0) { }

};

template <> class input<pss_int> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_int(), 0) { }

	input(const Scope &name, const pss_int &t_decl) :
		FieldItem(name, FieldItem::AttrInput, t_decl, 0) { }

	input(const Scope &name, uint32_t w) :
		FieldItem(name, FieldItem::AttrInput, pss_int(w), 0) { }

};

template <> class input<unsigned int> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_bit(32), 0) { }

};

template <> class input<int> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_int(32), 0) { }

};

template <> class input<unsigned short> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_bit(16), 0) { }

};

template <> class input<short> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_int(16), 0) { }

};

template <> class input<unsigned char> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_bit(8), 0) { }

};

template <> class input<char> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_int(8), 0) { }

};

template <> class input<bool> : public FieldItem {
public:
	input(const Scope &name) :
		FieldItem(name, FieldItem::AttrInput, pss_bool(), 0) { }

};

} /* namespace pss */

#endif /* INCLUDED_INPUT_H */
