/*
 * resource_struct.h
 *
 *  Created on: Mar 17, 2017
 *      Author: ballance
 */

#ifndef INCLUDE_RESOURCE_STRUCT_H_
#define INCLUDE_RESOURCE_STRUCT_H_

//class structure { };
//class scope { };

template <class T=structure> class resource_struct : public T {
public:
	resource_struct(const scope &p);

};

class processor_s : public resource_struct<> {
public:
	processor_s(const scope &p);
};

class my_data_s : public structure {
public:
	my_data_s(const scope &p);
};

class my_data_resource : public resource_struct<my_data_s> {
public:
	my_data_resource(const scope &p);
};

#endif /* INCLUDE_RESOURCE_STRUCT_H_ */
