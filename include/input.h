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
#include "prv/attr_item.h"
#include "scope.h"
#include "pss_bit.h"
#include "pss_int.h"

namespace pss {

using namespace prv;

template <class T> class input : public vendor::input_impl<T> {

public:
	/**
	 * This constructor is used for specifying an action input field
	 */
	input(const std::string &name);

	virtual ~input();

};

template <> class input<pss_bit> : public attr_item {
public:
	input(const scope &name);

	input(const scope &name, const pss_bit &t_decl);

	input(const scope &name, uint32_t w);

};

template <> class input<pss_int> : public attr_item {
public:
	input(const scope &name);

	input(const scope &name, const pss_int &t_decl);

	input(const scope &name, uint32_t w);

};

template <> class input<unsigned int> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<int> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<unsigned short> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<short> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<unsigned char> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<char> : public attr_item {
public:
	input(const scope &name);

};

template <> class input<bool> : public attr_item {
public:
	input(const scope &name);

};

} /* namespace pss */

#endif /* INCLUDED_INPUT_H */
