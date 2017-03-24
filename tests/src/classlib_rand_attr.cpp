/*
 * classlib_rand_attr.cpp
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
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class data_s : public memory_struct {
	pss_ctor(data_s, memory_struct);

	rand_attr<pss_bit>				data{"data", 8};
	rand_attr<pss_bit>				address{"address", 32};

	constraint address_c { address >= 0x1000 && address <= 0x1FFF };
};
pss_type(data_s);



class data_s_ext : public data_s {
	pss_ctor(data_s_ext, data_s);

	rand_attr<pss_bit>				burst_len{"burst_len", 4};

};
pss_type(data_s_ext);

class my_comp : public component {
	pss_component_ctor(my_comp);

#ifdef UNDEFINED
	class data_s2 : public pss_struct {
		pss_struct_ctor(data_s2);
	};
	pss_type(data_s2);

	class data_s2_ext : public data_s2 {
		pss_ctor(data_s2_ext, data_s2);
	};
	pss_type(data_s2_ext);
#endif

	class my_action : public action {
		pss_ctor(my_action, action);

//		rand_attr<uint8_t>			f1 {"f1"};
//		rand_attr<pss_bit>			f2 {"f2", 21};
		data_s						f2 {"f2"};
		rand_attr<data_s>			f3 {"f3"};
//		rand_attr<data_s_ext>		f4 {"f4"};
	};
	pss_type(my_action);

};
pss_type(my_comp);


