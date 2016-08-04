/*
 * classlib_missing_type_rgy.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "pss_tests.h"


static class missing_type_rgy : public Struct {
public:

	missing_type_rgy(BaseItem *p=0, pss_name name="missing_type_rgy") : Struct(p, name) { }

} missing_type_rgyT;

static class instance_s : public Struct {
public:

	Rand<missing_type_rgy>		f {this, "f"};

	instance_s(BaseItem *p=0, pss_name name="instance_s") : Struct(p, name) { }

} instance_sT;



