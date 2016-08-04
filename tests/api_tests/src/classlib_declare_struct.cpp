/*
 * classlib_declare_struct.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class data_s : public MemoryStruct {
	pss_ctor(data_s, MemoryStruct);

	Rand<Bit<7,0>>				pss_field(data);
	Rand<Bit<31,0>>				pss_field(address);

	pss_constraint(address_c,
		address >= 0x1000 && address <= 0x1FFF);
};
pss_global_type(data_s);



class data_s_ext : public data_s {
	pss_ctor(data_s_ext, data_s);

	Rand<Bit<3,0>>				pss_field(burst_len);

};
pss_global_type(data_s_ext);

class my_comp : public Component {
	pss_component_ctor(my_comp);

	class data_s2 : public Struct {
		pss_struct_ctor(data_s2);
	};
	pss_type(data_s2);

	class data_s2_ext : public data_s2 {
		pss_ctor(data_s2_ext, data_s2);
	};
	pss_type(data_s2_ext);

};
pss_global_type(my_comp);


