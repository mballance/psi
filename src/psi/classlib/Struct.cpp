/*
 * Struct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Struct.h"

#include "classlib/TypeRegistry.h"

namespace psi {

Struct::Struct() : Type(Type::TypeStruct, "", nullptr),
		m_structType(Struct::Base),
		m_superRef(Type::TypeRef, nullptr), m_super(nullptr) { }

Struct::Struct(
		const std::string 	&name,
		Type 				*p,
		Struct 				&super_type) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(Struct::Base),
				m_superRef(Type::TypeRef, nullptr) {

	if (&super_type == &None) {
		m_super = nullptr;
	} else {
		m_super = &super_type;
	}
}

Struct::Struct(
		const std::string 	&name,
		Type 				*p,
		const std::string	&super_name) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(Struct::Base),
				m_superRef(Type::TypeRef, super_name, nullptr),
				m_super(&m_superRef) {
}

Struct::Struct(
		Struct::StructType	t,
		const std::string 	&name,
		Type 				*p,
		Struct 				&super_type) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(t),
				m_superRef(Type::TypeRef, nullptr) {

	if (&super_type == &None) {
		m_super = nullptr;
	} else {
		m_super = &super_type;
	}
}

Struct::Struct(
		Struct::StructType	t,
		const std::string 	&name,
		Type 				*p,
		const std::string	&super_name) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(t),
				m_superRef(Type::TypeRef, super_name, nullptr),
				m_super(&m_superRef) {
}

Struct::~Struct() {
	// TODO Auto-generated destructor stub
}

Struct Struct::None; // = Struct("", nullptr);

} /* namespace psi */
