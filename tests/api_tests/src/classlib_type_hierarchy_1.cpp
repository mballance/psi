/*
 * classlib_type_hierarchy_1.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class Base : public Struct {
public:
	pss_ctor(Base, Struct);

	Rand<Bit<7,0>>		pss_field(a);
	Rand<Bit<7,0>>		pss_field(b);

	Constraint c {this, "c", {
			a == 5,
			b == 6
	}};

};
pss_global_type(Base);

class Ext : public Base {
public:
	pss_ctor(Ext, Base);

	Constraint c {this, "c", {
			a == 7,
			b == 8
	}};
};
pss_global_type(Ext);


