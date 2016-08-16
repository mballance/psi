#include "pss_tests.h"

class top_comp : public Component {
public:
	top_comp(const Scope &p) : Component(this) { }

	class do_something : public Action {
	public:
		do_something(Scope p) : Action(p) { }
	};
	TypeDecl<do_something> _do_something_t{this};

	class top_action : public Action {
	public:
		top_action(const Scope &p) : Action(this) { }

		GraphNode<do_something>	a{this, "a"},
		                        b{this, "b"},
							    c{this, "c"};

		Graph g {this, 
			a,
			b,
			Parallel {
				a,
				Repeat { 5,
					Sequential {
						b,
						c
					}
				}
			}
		};

	};
	TypeDecl<top_action> _top_action_t{this};

};
TypeDecl<top_comp> _top_comp_t;
