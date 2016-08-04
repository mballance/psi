/*
 * constraint_ifelse_test.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class constraint_ifelse_test : public Struct {
public:
	pss_struct_ctor(constraint_ifelse_test);

	Rand<Bit<>>			pss_field(control);
	Rand<Bit<31,1>>		pss_field(address);
	Rand<Bit<31,1>>		pss_field(data);

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

	Constraint c3 {this,
		If {
			(control == 1), {
						address == 1
			}, /* else */ {
					If {
						(address == 20), {
							data == 10
						}, /* else */ {
							data == 50
						}
					}
			}
		}
	};

};
pss_global_type(constraint_ifelse_test);


