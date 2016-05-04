/*
 * constraint_ifelse_test.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "psi.h"

using namespace psi;

static class constraint_ifelse_test : public Struct {
public:
	constraint_ifelse_test(const std::string &name="constraint_ifelse_test", Type *p=0) : Struct(name, p) { }

	Rand<Bit<>>					control {"control", this};
	Rand<Bit<31,1>>				address {"address", this};
	Rand<Bit<31,1>>				data 	{"data", this};

	Constraint c1 {this,
		If {(control == 1), address < 10}
	};

	Constraint c2 {this,
		If {
			(control == 1), // params okay
			{
				address < 10,
				data > 0 && data < 100
			}, /* else */ {
				address > 10,
				data > 10 && data < 1000
			}
		}
	};

} constraint_ifelse_testT;


