/*
 * classlib_declare_action.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class data_s : public MemoryStruct {
public:

	data_s(const Scope &p, psi_name name="data_s") : MemoryStruct(this, name) { }

	Rand<Bit<7,0>>				data    {this, "data"};
	Rand<Bit<31,0>>				address {this, "address"};

	Constraint address_c {this,
		address >= 0x1000 && address <= 0x1FFF
	};
};
TypeDecl<data_s>	data_sT;

class rw_comp : public Component {
public:

	rw_comp(BaseItem *p=0, psi_name name="rw_comp") : Component(p, name) { }

	class processor_s : public ResourceStruct {
	public:

		processor_s(const Scope &p, psi_name name="processor_s") : ResourceStruct(this, name) { }

		Constraint resource_c {this, instance_id == 1};

	};
	TypeDecl<processor_s> processor_sT {this};

	class write_data : public Action {
	public:

		write_data(const Scope &p, psi_name name="write_data") : Action(this, name) { }

		// When instantiating a field of a non-primitive type, a reference
		// to its declaration must be provided. This can be done via a reference
		// to the type-declaration object (data_sT), or with a string name.
		// Note that C++ construction-order rules require us to use the 'string'
		// form for proc, since it's declared in the same component.
		Output<data_s>			out_data	{this,"out_data"};
		Lock<processor_s>		proc 		{this,"proc"};
	};
	TypeDecl<write_data> write_dataT {this};

	class write_data2 : public write_data {
	public:

		write_data2(const Scope &p, psi_name name="write_data2") : write_data(this, name) { }

	};
	TypeDecl<write_data2> write_data2T {this};

};
TypeDecl<rw_comp>		rw_compT;


