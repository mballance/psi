/*
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 */
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

		Graph g {this, 
			a,
			b,
			Parallel {
				a,
				Repeat {5,
						c
				},
				a
			}
		};

	};
	pss_type(top_action);

};
pss_global_type(top_comp);
