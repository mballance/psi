/*
 * PssMacros.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef INCLUDED_PSS_MACROS_H
#define INCLUDED_PSS_MACROS_H

#ifdef PSS_HAVE_CXX_11

/**
 * Helper macro for declaring fields.
 */
#define pss_field(name) name { this, #name }

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
	_name (const Scope &p) : _super(this) { }

#define pss_constraint(_name, _body) \
		Constraint _name {this, #_name, _body};

#define pss_action_ctor(_name) \
		pss_ctor(_name, Action)

#define pss_component_ctor(_name) \
		pss_ctor(_name, Component)

#define pss_package_ctor(_name) \
		pss_ctor(_name, Package)

#define pss_struct_ctor(_name) \
		pss_ctor(_name, Struct)

#endif /* End PSS_HAVE_CXX_11 */

/**
 * Helper macro to register a global namespace type
 */
#define pss_global_type(_name) \
		TypeDecl<_name>		_##_name##_t

#ifdef PSS_HAVE_CXX_11
/**
 * Helper macro to register a non-global namespace type
 */
#define pss_type(_name) \
		TypeDecl<_name>		_##_name##_t {this}

#endif /* End PSS_HAVE_CXX_11 */

#define pss_typeid(T) \
	(*TypeDecl<T>::type_id())

#endif /* INCLUDED_PSS_MACROS_H */
