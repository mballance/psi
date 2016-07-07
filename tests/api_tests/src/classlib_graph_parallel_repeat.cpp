#include "psi_tests.h"

class top_comp : public Component {
public:
	top_comp(BaseItem *p=0, psi_name name="top_comp") : Component(p, name) { }

	class at : public Action {
	public:
		Rand<Bit<3,0>>		field {this, "field"};

		at(BaseItem *p=0, psi_name name="at") : Action(p, name) { }
	};
	TypeDecl<at> _at {this};

	class top_action : public Action {
	public:
		Field<at>				a{this, "a"}, b{this, "b"}, c{this, "c"};

		top_action(BaseItem *p=0, psi_name name="top_action") : Action(p, name) { }

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
	TypeDecl<top_action> _top_actionT {this};

};
TypeDecl<top_comp> _top_compT;
