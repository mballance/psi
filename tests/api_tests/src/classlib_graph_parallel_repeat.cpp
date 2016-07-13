#include "psi_tests.h"

class top_comp : public Component {
public:
	psi_ctor(top_comp, Component);

	class at : public Action {
	public:
		psi_ctor(at, Action);

		Rand<Bit<3,0>>		psi_field(field);
	};
	psi_type(at);

	class top_action : public Action {
	public:
		psi_ctor(top_action, Action);

		Field<at>		psi_field(a);
		Field<at>		psi_field(b);
		Field<at>		psi_field(c);

		Graph g {this, {
			a,
			b,
			Parallel {
				a,
				Repeat {5,
					{
						c
					}
				},
				a
			}
		}
		};

	};
	psi_type(top_action);

};
psi_global_type(top_comp);
