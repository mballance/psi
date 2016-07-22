/*
 * classlis_dac_tutorial_data_flow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

class S : public Struct {
public:
	psi_ctor(S, Struct);

};
psi_global_type(S);

class CA : public Component {
public:
	psi_ctor(CA, Component);

	class A : public Action {
	public:
		psi_ctor(A, Action);

		Output<S>			psi_field(out_s);
	};
	psi_type(A);

};
psi_global_type(CA);

class CB : public Component {
public:
	psi_ctor(CB, Component);

	class B : public Action {
	public:
		psi_ctor(B, Action);

		Input<S>			psi_field(in_s);
	};
	psi_type(B);
};
psi_global_type(CB);

class static_structure : public Component {
public:

	Field<CA>			psi_field(ca1);
	Field<CA>			psi_field(ca2);
	Field<CB>			psi_field(cb1);
	Field<CB>			psi_field(cb2);

	psi_ctor(static_structure, Component);

	// TODO:
	Bind b2 { this,
			// ca1.A.out_s
			ca1._A_t.out_s,
			ca2._A_t.out_s,
			cb1._B_t.in_s,
			cb2._B_t.in_s };

	class entry_point : public Action {
	public:
		psi_ctor(entry_point, Action);

	};
	psi_type(entry_point);

};
psi_global_type(static_structure);



