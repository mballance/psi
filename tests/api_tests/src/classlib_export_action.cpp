/*
 * classlib_export_action.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class my_comp : public Component {
public:
	my_comp(BaseItem *p=0, psi_name name="my_comp") : Component(p, name) { }

	class my_action : public Action {
	public:
		Rand<Bit<1,0>>				mode  {this, "mode"};
		Rand<Bit<1,0>>				mode2 {this, "mode2"};
		my_action(BaseItem *p=0, psi_name name="my_action") : Action(p, name) { }
	};
	TypeDecl<my_action> my_actionT {this};

};
TypeDecl<my_comp> my_compT;

class top_pkg : public Package {
public:
	top_pkg(BaseItem *p=0, psi_name name="top_pkg") : Package(p, name) { }

	ExportAction exp1 {this, TypeDecl<my_comp::my_action>::type_id()};

};
TypeDecl<top_pkg> top_pkgT;



