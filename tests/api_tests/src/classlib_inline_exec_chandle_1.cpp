/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class my_class {
public:

	uint32_t get_value() { return 0x27; }
};

class top : public Component {
public:
	pss_component_ctor(top);

	class entry_point : public Action {
	public:
		pss_action_ctor(entry_point);

		Field<Chandle<my_class>>		pss_field(p1);
		Field<Bit<31,0>>				pss_field(p2);
		Field<Chandle<>>				pss_field(p3);

		Exec pre_solve_e {this, Exec::PreSolve};

		Exec post_solve_e {this, Exec::PostSolve};

		void pre_solve() {
			p1.set(new my_class());
		}

		void post_solve() {
			p2.set(p1.get()->get_value());
			p3.set(0);
		}
	};
	pss_type(entry_point);

};
pss_global_type(top);

/**
 * Test code
 */
void exec_model(IModel *model) {
	const char *initial =
R"(
		<values>
			<chandle path="top.entry_point.p1">0</chandle>
			<bit path="top.entry_point.p2">0</bit>
			<chandle path="top.entry_point.p3">0x10001000</chandle>
		</values>
)";

	InlineExecInitialValueTestFixture::run(
			model,
			"top",
			"entry_point",
			initial);
}
