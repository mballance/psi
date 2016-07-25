/*
 * classlib_declare_action.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class data_s : public MemoryStruct {
public:

	psi_ctor(data_s, MemoryStruct);

	Rand<Bit<7,0>>				psi_field(data);
	Rand<Bit<31,0>>				psi_field(address);

	psi_constraint(address_c,
			{address >= 0x1000 && address <= 0x1FFF});
};
psi_global_type(data_s);

class rw_comp : public Component {
public:

	psi_ctor(rw_comp, Component);

	class processor_s : public ResourceStruct {
	public:

		psi_ctor(processor_s, ResourceStruct);

		psi_constraint(resource_c, {instance_id == 1});

	};
	psi_type(processor_s);

	class write_data : public Action {
	public:

		psi_ctor(write_data, Action);

		// When instantiating a field of a non-primitive type, a reference
		// to its declaration must be provided. This can be done via a reference
		// to the type-declaration object (data_sT), or with a string name.
		// Note that C++ construction-order rules require us to use the 'string'
		// form for proc, since it's declared in the same component.
		Output<data_s>			psi_field(out_data);
		Lock<processor_s>		psi_field(proc);
	};
	psi_type(write_data);

};
psi_global_type(rw_comp);


