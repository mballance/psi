/*
 * constraint_basics_test.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class constraint_basics_test : public Struct {
public:
	pss_struct_ctor(constraint_basics_test);

	Rand<Bit<31,0>>			pss_field(address);

	Constraint c0 {this, address >= 0x1000 }; // named constraint

	Constraint c1 {this, address >= 0x1000 && address <= 0x1fff }; // anonymous constraint

	Constraint c2 {this, {
			address >= 0x1000 , // comma used as constraint-statement separator
			                    // comma-separated statements must be surrounded in parens or braces
			address <= 0x1fff
			} };

};
pss_global_type(constraint_basics_test);

