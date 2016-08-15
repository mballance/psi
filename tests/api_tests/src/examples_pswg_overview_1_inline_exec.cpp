/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

int refmodel_get_next_value() {
	return 27;
}

class top : public Component {
public:
	top(const Scope &p) : Component(this) { }

	class entry_point : public Action {
	public:
		entry_point(const Scope &p) : Action(this) { }

		Rand<Bit<7,0>>		p1{this, "p1"};
		Rand<Bit<31,0>>		p2{this, "p2"};
		Rand<Bit<31,0>>		p3{this, "p3"};
		Field<Bit<31,0>>	p4{this, "p4"};
		Field<Bit<31,0>>	p5{this, "p5"};

		Exec register_pre_solve {this, Exec::PreSolve};

		Exec register_post_solve {this, Exec::PostSolve};

		void pre_solve() {
			// Set p4 based on calling a generation-time method
			p4.set(refmodel_get_next_value());
		}

		void post_solve() {
			// Set p5 based on a calculated value
			p5.set(p1.get() + p2.get());
			p5.set(p1.get() + p2.get()+1);
		}
	};
	TypeDecl<entry_point> _entry_point_t{this};

};
TypeDecl<top> _top_t;

/**
 * Test code
 */
void exec_model(IModel *model) {
	const char *initial =
R"(
		<values>
			<bit path="top.entry_point.p1">0x01</bit>
			<bit path="top.entry_point.p2">0x20</bit>
			<bit path="top.entry_point.p3">0x30</bit>
			<bit path="top.entry_point.p4">0x00</bit>
			<bit path="top.entry_point.p5">0x00</bit>
		</values>
)";

	InlineExecInitialValueTestFixture::run(
			model,
			"top",
			"entry_point",
			initial);
}
