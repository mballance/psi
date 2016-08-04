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

	// Declare coverspec type
	class my_coverspec : public Coverspec {
	public:
		// ?? Best way to specify the interface list?
		// Need to be able to access from the outside somehow (?)
		// Need to have a field-like thing to reference inside
		//  the coverspec

		// Coverpoint specifies expressions related to input fields
		Coverpoint			cp1 {this, "cp1", /* Expression */ };

		// Cross specifies references to coverpoints
		Cross				cross1 {this, "cross1", /* List of coverpoints */ };

	};

	// Instantiate coverspec, specifying binding to I/O variables

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


