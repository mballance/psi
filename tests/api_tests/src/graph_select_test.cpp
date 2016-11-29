/*
 * graph_select_test.h
 *
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
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class top_c : public Component {
public:
	pss_ctor(top_c, Component);

	class A1 : public Action {
	public:
		pss_ctor(A1, Action);

	};
	pss_type(A1);

	class graph_select_test : public Action {
	public:
		pss_ctor(graph_select_test, Action);

		Field<A1>			pss_field(a1_1);
		Field<A1>			pss_field(a1_2);
		Field<A1>			pss_field(a1_3);
		Field<A1>			pss_field(a1_4);

		Graph graph {this, {
				Select {
						Sequential{a1_1, a1_2},
						Sequential{a1_3, a1_4}
				},
				Parallel {
						Sequential{a1_1, a1_2},
						Sequential{a1_3, a1_4}
				}
		}
		};
	};
	pss_type(graph_select_test);

};
pss_global_type(top_c);

