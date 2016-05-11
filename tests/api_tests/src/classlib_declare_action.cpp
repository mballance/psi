/*
 * classlib_declare_action.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class data_s : public MemoryStruct {
public:
	data_s(const std::string &name="data_s", Type *p=0) : MemoryStruct(name, p) { }

	Rand<Bit<7,0>>				data { "data", this };
	Rand<Bit<31,0>>				address { "address", this };

	Constraint address_c {this,
		address >= 0x1000 && address <= 0x1FFF
	};
} data_sT;

static class rw_comp : public Component {
public:

	rw_comp(const std::string &name="rw_comp", Type *p=nullptr) : Component(name, p) { }

	class processor_s : public ResourceStruct {
	public:

		processor_s(const std::string &name, Type *p) : ResourceStruct(name, p) { }

		Constraint resource_c {this, instance_id == 1};

	} processor_sT {"processor_s", this};

	class write_data : public Action {
	public:

		write_data(const std::string &name, Type *p) : Action(name, p) { }

		// When instantiating a field of a non-primitive type, a reference
		// to its declaration must be provided. This can be done via a reference
		// to the type-declaration object (data_sT), or with a string name.
		// Note that C++ construction-order rules require us to use the 'string'
		// form for proc, since it's declared in the same component.
		Output<data_s>			out_data	{"out_data", this, data_sT};
		Lock<processor_s>		proc 		{"proc", this, "processor_s"};
	} write_dataT {"write_data", this};

} rw_compT;


