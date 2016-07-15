/*
 * classlib_type_hierarchy_1.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

class Base : public Struct {
public:
	psi_ctor(Base, Struct);

	Rand<Bit<7,0>>		psi_field(a);
	Rand<Bit<7,0>>		psi_field(b);

	Constraint c {this, "c", {
			a == 5,
			b == 6
	}};

};
psi_global_type(Base);

class Ext : public Base {
public:
	psi_ctor(Ext, Base);

	Constraint c {this, "c", {
			a == 7,
			b == 8
	}};
};
psi_global_type(Ext);


