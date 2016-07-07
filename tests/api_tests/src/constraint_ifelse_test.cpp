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
	constraint_ifelse_test(BaseItem *p=0, const std::string &name="constraint_ifelse_test") : Struct(p, name) { }

	Rand<Bit<>>					control {this, "control"};
	Rand<Bit<31,1>>				address {this, "address"};
	Rand<Bit<31,1>>				data 	{this, "data"};

	Constraint c1 {this, "c1",
		If {(control == 1), address < 10}
	};

	Constraint c2 {this,
		If {
			(control == 1),
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


