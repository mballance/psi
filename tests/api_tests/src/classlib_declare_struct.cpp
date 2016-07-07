/*
 * classlib_declare_struct.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class data_s : public MemoryStruct {
public:
	data_s(BaseItem *p=0, psi_name name="data_s") : MemoryStruct(p, name) { }

	Rand<Bit<7,0>>				data    {this, "data"};
	Rand<Bit<31,0>>				address {this, "address"};

	Constraint address_c {this,
		address >= 0x1000 && address <= 0x1FFF
	};
};
TypeDecl<data_s> data_sT;


