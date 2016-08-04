/*
 * classlib_component_field_inst.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class my_comp1 : public Component {
public:
	pss_component_ctor(my_comp1);

};
pss_global_type(my_comp1);

class my_comp2 : public Component {
public:
	Field<my_comp1>			pss_field(f1);

	pss_component_ctor(my_comp2);

};
pss_global_type(my_comp2);



