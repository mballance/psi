/*
 * concept_walkthrough.cpp
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
#include "pss_tests.h"

class data_s : public memory_struct {
public:
	rand_attr<uint8_t>		pss_field(data);
	rand_attr<uint32_t>		pss_field(address);

	pss_ctor(data_s, memory_struct);

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

		output<data_s>			pss_field(out_data);
		lock<processor_s>		pss_field(proc);
	};
	pss_type(write_data);

	class read_data : public action {
	public:
		pss_ctor(read_data, action);

		input<data_s>			pss_field(in_data);
		lock<processor_s>		pss_field(proc);
	};
	pss_type(read_data);

};
pss_type(rw_comp);

class top_comp : public component {
public:
	pss_ctor(top_comp, component);

	class my_test2 : public action {
	public:
		pss_ctor(my_test2, action);

		// action instance needs to know the details of its type. This is
		// provided via a type-definition reference (eg _rw_comp._write_data)
		rw_comp::write_data		pss_field(wd1);
		rw_comp::read_data		pss_field(rd1);
		rw_comp::write_data		pss_field(wd2);
		rw_comp::read_data		pss_field(rd2);

		// Only a single activity is permitted per action
		activity g {
			sequence {
				wd1, rd1, wd2, rd2
			}
		};

		constraint addr_c {"addr_c", rd1.in_data.address != rd2.in_data.address };

	};
	pss_type(my_test2);

};
pss_type(top_comp);

class c_methods : public package {
public:
	pss_package_ctor(c_methods);

	// Prototypes for import functions
	import_func do_write {"do_write",
		{input<uint32_t>("addr"), input<uint32_t>("data")}
	};

	import_func do_check {"do_check",
		{input<uint32_t>("addr"), input<uint32_t>("data")}
	};

};
pss_type(c_methods);

class c_code : public package {
public:
	pss_ctor(c_code, package);

	// Declares an extension of 'write_data' to layer in the implementation
	class write_data_ext : public extend_action<rw_comp::write_data> {
	public:
		write_data_ext(const scope &p) : extend_action(this) { }

		// Example of a target-template exec block
		exec do_write_body {exec::Body, "C", R"(
				do_write({{address}}, {{data}}
				)"
		};

		exec do_write_body_native {exec::Body,
			_c_methods_t.do_write(out_data.address, out_data.data)
		};
	};
	type_decl<write_data_ext> _write_data_ext_t;

	class read_data_ext : public extend_action<rw_comp::read_data> {
	public:

		read_data_ext(const scope &p) : extend_action(this) {}

		rand_attr<pss_bit>			tmp{"tmp", 4};

		exec do_check_body_native {exec::Body,
			_c_methods_t.do_check(in_data.address, in_data.data)
		};
	};
	type_decl<read_data_ext> _read_data_ext_t;

};
pss_type(c_code);

