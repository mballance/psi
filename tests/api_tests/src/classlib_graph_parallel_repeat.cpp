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

class top_comp : public component {
public:
	pss_ctor(top_comp, component);

	class at : public action {
	public:
		pss_ctor(at, action);

		rand_attr<pss_bit<3,0>>		pss_field(field);
	};
	pss_type(at);

	class top_action : public action {
	public:
		pss_ctor(top_action, action);

		attr<at>		pss_field(a);
		attr<at>		pss_field(b);
		attr<at>		pss_field(c);

		graph g {this, 
			a,
			b,
			parallel {
				a,
				repeat {5,
						c
				},
				a
			}
		};

	};
	pss_type(top_action);

};
pss_global_type(top_comp);
