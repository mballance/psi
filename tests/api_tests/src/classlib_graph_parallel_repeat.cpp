#include "psi_tests.h"

class top_comp : public Component {
public:
	TypeRgy<top_comp>		type_id {this};

	top_comp(Type *p=0, psi_name name="top_comp") : Component(p, name) { }

	class at : public Action {
	public:
		TypeRgy<at>			type_id {this};

		Rand<Bit<3,0>>		field {this, "field"};

		at(Type *p=0, psi_name name="at") : Action(p, name) { }
	} _at {this};

	class top_action : public Action {
	public:
		TypeRgy<top_action>		type_id {this};
		Field<at>				a{this, "a"}, b{this, "b"}, c{this, "c"};

		top_action(Type *p=0, psi_name name="top_action") : Action(p, name) { }

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

	} _top_actionT {this};

} _top_compT;
