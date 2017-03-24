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

//<vendor>
#include "vendor/type_decl_impl.h"
//</vendor>

namespace pss {

template <class T> class type_decl : public vendor::type_decl_impl<T> {
public:

	/**
	 *
	 */
	type_decl();

	/**
	 * Returns
	 */
	static T *id();

};

}

// <vendor>
#include "vendor/type_decl.hpp"
// </vendor>
#endif /* INCLUDED_TYPE_DECL_H */
