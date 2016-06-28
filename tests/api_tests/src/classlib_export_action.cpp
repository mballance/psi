/*
 * classlib_export_action.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class my_comp : public Component {
public:
	TypeRgy<my_comp>		type_id {this};

	my_comp(Type *p=0, psi_name name="my_comp") : Component(p, name) { }

	class my_action : public Action {
	public:
		TypeRgy<my_action>		type_id {this};

		Rand<Bit<1,0>>				mode  {this, "mode"};
		Rand<Bit<1,0>>				mode2 {this, "mode2"};
		my_action(Type *p=0, psi_name name="my_action") : Action(p, name) { }
	} my_actionT {this};

} my_compT;

static class top_pkg : public Package {
public:
	TypeRgy<top_pkg>		type_id {this};

	top_pkg(Type *p=0, psi_name name="top_pkg") : Package(p, name) { }

	ExportAction exp1 {this, TypeRgy<my_comp::my_action>::type_id()};

//	ExportAction exp2 {this, TypeRgy<my_comp::my_action>::type_id(),
//		 (my_compT.my_actionT.mode, my_compT.my_actionT.mode2)};

} top_pkgT;



