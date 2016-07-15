/*
 * classlib_declare_struct.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class data_s : public MemoryStruct {
	psi_ctor(data_s, MemoryStruct);

	Rand<Bit<7,0>>				psi_field(data);
	Rand<Bit<31,0>>				psi_field(address);

	psi_constraint(address_c,
		address >= 0x1000 && address <= 0x1FFF);
};
psi_global_type(data_s);



class data_s_ext : public data_s {
	psi_ctor(data_s_ext, data_s);

	Rand<Bit<3,0>>				psi_field(burst_len);

};
psi_global_type(data_s_ext);

class my_comp : public Component {
	psi_component_ctor(my_comp);

	class data_s2 : public Struct {
		psi_struct_ctor(data_s2);
	};
	psi_type(data_s2);

	class data_s2_ext : public data_s2 {
		psi_ctor(data_s2_ext, data_s2);
	};
	psi_type(data_s2_ext);

};
psi_global_type(my_comp);


