/*
 * Struct.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef STRUCT_H_
#define STRUCT_H_
#include <string>

#include "Type.h"

namespace psi {

class Struct : public Type {

public:
	enum StructType {
		Base,
		Memory,
		Stream,
		Resource
	};

	public:

		virtual ~Struct();

	protected:


		Struct(
				const std::string 	&name,
				Type 				*p=nullptr,
				Struct 				&super_type=None);

		Struct(
				const std::string 	&name,
				Type 				*p,
				const std::string	&super_name);

		Struct(
				StructType			t,
				const std::string 	&name,
				Type 				*p=nullptr,
				Struct 				&super_type=None);

		Struct(
				StructType			t,
				const std::string 	&name,
				Type 				*p,
				const std::string	&super_name);

	private:
		Struct();

	private:
		StructType						m_structType;
		Type							m_superRef;
		Type							*m_super;

	protected:
		static Struct					None;
};

} /* namespace psi */

#endif /* STRUCT_H_ */
