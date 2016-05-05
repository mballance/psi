/*
 * constraint_basics_test.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "psi.h"

using namespace psi;

static class constraint_basics_test : public Struct {
public:
	constraint_basics_test(const std::string &name="constraint_basics_test", Type *p=nullptr) :
		Struct(name, p) { }

	virtual ~constraint_basics_test() { };

	Rand<Bit<31,0>>				address {"address", this};

	Constraint c0 {"c0", this, address >= 0x1000 }; // named constraint

	Constraint c1 {this, address >= 0x1000 && address <= 0x1fff }; // anonymous constraint

	Constraint c2 {this, {
			address >= 0x1000 , // comma used as constraint-statement separator
			                    // comma-separated statements must be surrounded in parens or braces
			address <= 0x1fff
			} };

} constraint_basics_testT;

