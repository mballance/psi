/*
 * classlib_export_action.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class my_comp : public Component {
public:
	pss_component_ctor(my_comp);

	class my_action : public Action {
	public:
		pss_action_ctor(my_action);

		Rand<Bit<1,0>>		pss_field(mode);
		Rand<Bit<1,0>>		pss_field(mode2);
	};
	pss_type(my_action);
};
pss_global_type(my_comp);

class top_pkg : public Package {
public:
	pss_package_ctor(top_pkg);

	Export<my_comp::my_action> exp1 {this};
};
pss_global_type(top_pkg);

class top_pkg2 : public Package {
public:
	pss_package_ctor(top_pkg2);

	// Export the 'mode' field as a method parameter
	Export<my_comp::my_action> exp1 {this, {exp1.mode}};
};
pss_global_type(top_pkg2);


