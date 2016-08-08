#include "pss_tests.h"

class top_comp : public Component {
public:
	pss_ctor(top_comp, Component);

	class at : public Action {
	public:
		pss_ctor(at, Action);

		Rand<Bit<3,0>>		pss_field(field);
	};
	pss_type(at);

	class top_action : public Action {
	public:
		pss_ctor(top_action, Action);

		Field<at>		pss_field(a);
		Field<at>		pss_field(b);
		Field<at>		pss_field(c);

		Graph g {this, {
			a,
			b,
			Parallel {
				a,
				Repeat {5,
						c
				},
				a
			}
		}
		};

	};
	pss_type(top_action);

};
pss_global_type(top_comp);
