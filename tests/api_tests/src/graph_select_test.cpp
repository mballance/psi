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

class top_c : public component {
public:
	pss_ctor(top_c, component);

	class A1 : public action {
	public:
		pss_ctor(A1, action);

	};
	pss_type(A1);

	class graph_select_test : public action {
	public:
		pss_ctor(graph_select_test, action);

		attr<A1>			pss_field(a1_1);
		attr<A1>			pss_field(a1_2);
		attr<A1>			pss_field(a1_3);
		attr<A1>			pss_field(a1_4);

		graph graph {this, {
				pss_select {
						sequence{a1_1, a1_2},
						sequence{a1_3, a1_4}
				},
				parallel {
						sequence{a1_1, a1_2},
						sequence{a1_3, a1_4}
				}
		}
		};
	};
	pss_type(graph_select_test);

};
pss_global_type(top_c);

