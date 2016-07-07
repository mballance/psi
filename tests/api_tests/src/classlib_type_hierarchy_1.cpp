/*
 * classlib_type_hierarchy_1.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

class Base : public Struct {
public:
	TypeRgy<Base>			type_id {this};

	Base(BaseItem *p=0, psi_name name="Base", Struct *super=0) : Struct(p, name, super) { }

	Rand<Bit<7,0>>			a {this, "a"};
	Rand<Bit<7,0>>			b {this, "b"};

	Constraint c {this, "c", {
			a == 5,
			b == 6
	}};

} BaseT;

class Ext : public Base {
public:
	TypeRgy<Ext>			type_id {this};

	Ext(BaseItem *p=0, psi_name name="Ext", Struct *super=TypeRgy<Base>::type_id()) :
		Base(p, name, super) { }

	Constraint c {this, "c", {
			a == 7,
			b == 8
	}};
} ExtT;


