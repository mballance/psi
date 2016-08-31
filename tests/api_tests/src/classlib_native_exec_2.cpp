/*
 * classlib_native_exec_2.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class c_methods : public Package {
public:
	c_methods(const Scope &p) : Package(this) { }

	ImportFunc func {this, "func",
		{Input<Bit<31,0>>("a")}
	};
};
TypeDecl<c_methods> _c_methods_t;

class top_comp : public Component {
public:
	top_comp(const Scope &p) : Component(this) { }

	class entry_point : public Action {
	public:
		entry_point(const Scope &p) : Action(this) { }

		Field<Bit<31,0>>			f1 {this, "f1"};
		Field<Bit<31,0>>			f2 {this, "f2"};


		Exec body_e {this, Exec::Body, {
			f2 = 1,
			f1 = _c_methods_t.func(1),
			f2 += 2,
			f1 += _c_methods_t.func(2),
			f2 -= 3,
			f1 -= _c_methods_t.func(2),
			f2 <<= 4,
			f1 <<= _c_methods_t.func(4),
			f2 >>= 5,
			f1 >>= _c_methods_t.func(5),
			f2 &= 6,
			f1 &= _c_methods_t.func(6),
			f2 |= 7,
			f1 |= _c_methods_t.func(7)
		}
		};
	};
	TypeDecl<entry_point>		_entry_point_t{this};

};
TypeDecl<top_comp> _top_comp_t;



