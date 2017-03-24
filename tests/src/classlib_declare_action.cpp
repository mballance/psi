/*
 * classlib_declare_action.cpp
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
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class data_s : public memory_struct {
public:

	pss_ctor(data_s, memory_struct);

	rand_attr<pss_bit>			data {"data", 8};
	rand_attr<pss_bit>			address{"address", 32};

	constraint address_c {address >= 0x1000 && address <= 0x1FFF};
};
pss_type(data_s);

class rw_comp : public component {
public:

	pss_ctor(rw_comp, component);

	class processor_s : public resource_struct {
	public:

		pss_ctor(processor_s, resource_struct);

		constraint resource_c {instance_id == 1};

	};
	pss_type(processor_s);

	class write_data : public action {
	public:

		pss_ctor(write_data, action);

		// When instantiating a field of a non-primitive type, a reference
		// to its declaration must be provided. This can be done via a reference
		// to the type-declaration object (data_sT), or with a string name.
		// Note that C++ construction-order rules require us to use the 'string'
		// form for proc, since it's declared in the same component.
		output<data_s>			pss_field(out_data);
		lock<processor_s>		pss_field(proc);
	};
	pss_type(write_data);

};
pss_type(rw_comp);


