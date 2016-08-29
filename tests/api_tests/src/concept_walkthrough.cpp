/*
 * concept_walkthrough.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class data_s : public MemoryStruct {
public:
	Rand<Bit<7,0>>		pss_field(data);
	Rand<Bit<31,0>>		pss_field(address);

	pss_ctor(data_s, MemoryStruct);

	Constraint address_c {this, address >= 0x1000 && address <= 0x1FFF};
};
pss_global_type(data_s);

class rw_comp : public Component {
public:

	pss_ctor(rw_comp, Component);

	class processor_s : public ResourceStruct {
	public:
		pss_ctor(processor_s, ResourceStruct);

		Constraint resource_c {this, instance_id == 1};

	};
	pss_type(processor_s);

	class write_data : public Action {
	public:
		pss_ctor(write_data, Action);

		Output<data_s>			pss_field(out_data);
		Lock<processor_s>		pss_field(proc);
	};
	pss_type(write_data);

	class read_data : public Action {
	public:
		pss_ctor(read_data, Action);

		Input<data_s>			pss_field(in_data);
		Lock<processor_s>		pss_field(proc);
	};
	pss_type(read_data);

};
pss_global_type(rw_comp);

class top_comp : public Component {
public:
	pss_ctor(top_comp, Component);

	class my_test2 : public Action {
	public:
		pss_ctor(my_test2, Action);

		// Action instance needs to know the details of its type. This is
		// provided via a type-definition reference (eg _rw_comp._write_data)
		Field<rw_comp::write_data>		pss_field(wd1);
		Field<rw_comp::read_data>		pss_field(rd1);
		Field<rw_comp::write_data>		pss_field(wd2);
		Field<rw_comp::read_data>		pss_field(rd2);

		// Only a single graph is permitted per action
		Graph graph {this,
			Sequential {
				wd1, rd1, wd2, rd2
			}
		};

		Constraint addr_c {this, "addr_c", rd1.in_data.address != rd2.in_data.address };

	};
	pss_type(my_test2);

};
pss_global_type(top_comp);

class c_methods : public Package {
public:
	pss_package_ctor(c_methods);

	// Prototypes for import functions
	ImportFunc do_write {this, "do_write",
//		{InParam<Bit<31,0>>("addr"), InParam<Bit<31,0>>("data")}
		(Input<Bit<31,0>>("addr"), Input<Bit<31,0>>("data"))
	};

	ImportFunc do_check {this, "do_check",
		{Input<Bit<31,0>>("addr"), Input<Bit<31,0>>("data")}
	};

};
pss_global_type(c_methods);

class c_code : public Package {
public:
	pss_ctor(c_code, Package);

	// Declares an extension of 'write_data' to layer in the implementation
	class write_data_ext : public ExtendAction<rw_comp::write_data> {
	public:
		write_data_ext(const Scope &p) : ExtendAction(this) { }

		// Example of a target-template exec block
		Exec do_write_body {this, Exec::Body, "C", R"(
				do_write({{address}}, {{data}}
				)"
		};

		Exec do_write_body_native {this, Exec::Body,
			_c_methods_t.do_write(out_data.address, out_data.data)
		};
	};
	TypeDecl<write_data_ext> _write_data_ext_t {this};

	class read_data_ext : public ExtendAction<rw_comp::read_data> {
	public:

		read_data_ext(const Scope &p) : ExtendAction(this) {}

		Rand<Bit<3,0>>			tmp{this, "tmp"};

		Exec do_check_body_native {this, Exec::Body,
			_c_methods_t.do_check(in_data.address, in_data.data)
		};
	};
	TypeDecl<read_data_ext> _read_data_ext_t {this};

};
pss_global_type(c_code);

