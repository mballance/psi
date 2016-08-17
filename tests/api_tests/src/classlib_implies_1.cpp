/*
 * classlib_implies_1.cpp
 *
 *  Created on: Aug 16, 2016
 *      Author: ballance
 */
#include "pss_tests.h"


class my_struct : public Struct {
public:
	my_struct(const Scope &p) : Struct(this) { }

	Rand<Bit<31,0>>				addr {this, "addr"};
	Rand<Bit<31,0>>				data {this, "data"};

	Constraint c { this, "c",
		{
			(addr == 5).implies(data == 2),
			(addr == 7).implies(
					data >= 0 && data <= 7
					)
		}
	};
};
TypeDecl<my_struct>		_my_struct_t;



