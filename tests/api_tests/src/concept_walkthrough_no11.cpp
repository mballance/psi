/*
 * concept_walkthrough.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */
#include "psi.h"
#include <stdio.h>

using namespace psi;

static class data_s : public MemoryStruct {

	public:
		Rand<Bit<7,0> >			data;
		Rand<Bit<31,0> >		address;


		Constraint *address_c;

		data_s(
			const std::string 		&name,
			Type 	*p=nullptr) :
				MemoryStruct(name, p),
				data("data", this),
				address("address", this) {

			address_c = new Constraint(this, address >= 0x1000 && address <= 0x1FFF);
		}


	// Register this type definition
} _data_s = data_s("data_s");

static class rw_comp : public Component {

	public:

	rw_comp(const std::string &name, Type *p=nullptr) :
		Component(name, p),
		_processor_s("processor_s", this),
		_write_data("write_data", this),
		_read_data("read_data", this) { }

	class processor_s : public ResourceStruct {
		public:

			Constraint *resource_c;

			processor_s(const std::string &name, Type *p) : ResourceStruct(name, p) {
				resource_c = new Constraint(this, instance_id == 1);
			}

	} _processor_s;

	class write_data : public Action {

		public:

			// When instantiating a field of a non-primitive type, a reference
			// to its declaration must be provided. This can be done via a reference
			// to the type-declaration object (_data_s), or with a string name.
			// Note that C++ construction-order rules require us to use the 'string'
			// form for proc, since it's declared in the same component.
			Output<data_s>			out_data;
			Lock<processor_s>		proc;

			write_data(const std::string &name, Type *p) :
				Action(name, p),
				out_data("out_data", this, _data_s),
				proc("proc", this, "processor_s") { }
	} _write_data;

	class read_data : public Action {

		public:
			read_data(const std::string &name, Type *p) :
				Action(name, p),
				in_data("in_data", this, _data_s),
				proc("proc", this, "processor_s") { }

			Input<data_s>			in_data;
			Lock<processor_s>		proc;
	} _read_data;

} _rw_comp = rw_comp("rw_comp");


static class top_comp : public Component {

	public:
		top_comp(const std::string &name, Type *p=nullptr) :
			Component(name, p),
			_my_test2("my_test2", this) { }

	class my_test2 : public Action {

		public:

			my_test2(const std::string &name, Type *p) :
				Action(name, p),
				wd1("wd1", this, _rw_comp._write_data),
				rd1("rd1", this, _rw_comp._read_data),
				wd2("wd2", this, _rw_comp._write_data),
				rd2("rd2", this, _rw_comp._read_data)
				{
					addr_c = new Constraint(this,
							rd1.in_data.address != rd2.in_data.address
					);
				}

			// Action instance needs to know the details of its type. This is
			// provided via a type-definition reference (eg _rw_comp._write_data)
			Field<rw_comp::write_data>		wd1;
			Field<rw_comp::read_data>		rd1;
			Field<rw_comp::write_data>		wd2;
			Field<rw_comp::read_data>		rd2;

			// TODO: Bind -- make static?

//#ifdef UNDEFINED
//			my_test2() {
//				bind(wd1.out_data, rd1.in_data);
//				bind(wd2.out_data, rd1.in_data);
//			};
//
//			// Only a single graph is permitted per action
//			Graph graph {
//				wd1, rd1, wd2, rd2,
//	//			select {
//	//
//	//			}
//			};
//
			Constraint *addr_c;

	} _my_test2; // Complete registration of this type

} _top_comp = top_comp("top_comp");

static class c_code : public Package {

	public:

		c_code(const std::string &name, Type *p=nullptr) :
			Package(name, p), _write_data_ext(this, _rw_comp._write_data) { }

		// Declares an extension of 'write_data' to layer in the implementation
		class write_data_ext : public ExtendAction<rw_comp::write_data> {
			public:
				write_data_ext(Type *p, rw_comp::write_data &t_ref) : ExtendAction(p, t_ref) { }

				/*
				ImportFunction			do_write {
					this, "do_write",
					{ParamW2<Int<31,0>>("addr")}
				};
				 */
		} _write_data_ext;

} _c_code = c_code("c_code");

