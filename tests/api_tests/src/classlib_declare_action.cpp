/*
 * classlib_declare_action.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class data_s : public MemoryStruct {
public:
	TypeRgy<data_s>		type_id {this};

	data_s(Type *p=0, psi_name name="data_s") : MemoryStruct(p, name) { }

	Rand<Bit<7,0>>				data    {this, "data"};
	Rand<Bit<31,0>>				address {this, "address"};

	Constraint address_c {this,
		address >= 0x1000 && address <= 0x1FFF
	};
} data_sT;

static class rw_comp : public Component {
public:
	TypeRgy<rw_comp>		type_id {this};

	rw_comp(Type *p=0, psi_name name="rw_comp") : Component(p, name) { }

	class processor_s : public ResourceStruct {
	public:
		TypeRgy<processor_s>		type_id {this};

		processor_s(Type *p=0, psi_name name="processor_s") : ResourceStruct(p, name) { }

		Constraint resource_c {this, instance_id == 1};

	} processor_sT {this};

	class write_data : public Action {
	public:
		TypeRgy<write_data>		type_id {this};

		write_data(Type *p=0, psi_name name="write_data") : Action(p, name) { }

		// When instantiating a field of a non-primitive type, a reference
		// to its declaration must be provided. This can be done via a reference
		// to the type-declaration object (data_sT), or with a string name.
		// Note that C++ construction-order rules require us to use the 'string'
		// form for proc, since it's declared in the same component.
		Output<data_s>			out_data	{this,"out_data"};
		Lock<processor_s>		proc 		{this,"proc"};
	} write_dataT {this};

} rw_compT;


