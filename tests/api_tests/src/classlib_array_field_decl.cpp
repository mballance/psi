/*
 * classlib_array_field_decl.cpp
 *
 *  Created on: Aug 4, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class my_struct : public Struct {
public:
	Field<Bit<3,0>>				pss_array_field(a, 5);
	Rand<Bit<3,0>>				pss_array_field(b, (5+7));

	pss_struct_ctor(my_struct);
};
pss_global_type(my_struct);



