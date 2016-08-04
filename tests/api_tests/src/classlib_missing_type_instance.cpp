/*
 * classlib_missing_type_instance.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "pss_tests.h"


class missing_type_instance : public Struct {
public:
	TypeRgy<missing_type_instance>		type_id {this};

	missing_type_instance(BaseItem *p=0, pss_name name="missing_type_instance") : Struct(p, name) { }

};

static class instance_s : public Struct {
public:

	Rand<missing_type_instance>		f {this, "f"};

	instance_s(BaseItem *p=0, pss_name name="instance_s") : Struct(p, name) { }

} instance_sT;



