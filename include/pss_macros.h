/*
 * pss_macros.h
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
 */
#ifndef INCLUDED_PSS_MACROS_H
#define INCLUDED_PSS_MACROS_H

/**
 * Helper macro for declaring fields.
 */
#define pss_field(name) name { #name }

/**
 * Helper macro for declaring array fields
 */
#define pss_array_field(name, array_dim) name { this, #name , array_dim }

/**
 * Helper macro for declaring the constructor
 * and type registration for PSI-derived classes
 */
#define pss_ctor(_name, _super) \
	public: \
	_name (const scope &p) : _super(this) { }

#define pss_constraint(_name, _body) \
		constraint _name {this, #_name, _body};

#define pss_action_ctor(_name) \
		pss_ctor(_name, action)

#define pss_component_ctor(_name) \
		pss_ctor(_name, component)

#define pss_package_ctor(_name) \
		pss_ctor(_name, package)

#define pss_struct_ctor(_name) \
		pss_ctor(_name, pss_struct)

/**
 * Helper macro to register a non-global namespace type
 */
#define pss_type(_name) \
		type_decl<_name>		_##_name##_t

#endif /* End PSS_HAVE_CXX_11 */

#define pss_typeid(T) \
	(*type_decl<T>::type_id())

