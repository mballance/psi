/*
 * classlib_export_action.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class my_comp : public Component {
public:
	my_comp(const std::string &name="my_comp", Type *p=0) : Component(name, p) { }

	class my_action : public Action {
	public:
		Rand<Bit<1,0>>				mode { "mode", this };
		Rand<Bit<1,0>>				mode2 { "mode2", this };
		my_action(const std::string &name, Type *p) : Action(name, p) { }
	} my_actionT {"my_action", this};

} my_compT;

static class top_pkg : public Package {
public:

	top_pkg(const std::string &name="top_pkg", Type *p=0) : Package(name, p) { }

	ExportAction exp1 {my_compT.my_actionT, this};

	ExportAction exp2 {my_compT.my_actionT, this,
		 (my_compT.my_actionT.mode, my_compT.my_actionT.mode2)};

} top_pkgT;



