/*
 * classlib_declare_struct.h
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

	Constraint address_c {this,
		address >= 0x1000 && address <= 0x1FFF
	};
};
TypeDecl<data_s> data_sT;


