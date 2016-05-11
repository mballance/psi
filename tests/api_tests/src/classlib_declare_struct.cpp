/*
 * classlib_declare_struct.h
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


