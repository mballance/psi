/*
 * PsiMacros.h
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
#ifndef INCLUDED_PSI_MACROS_H
#define INCLUDED_PSI_MACROS_H

#ifdef PSI_HAVE_CXX_11

/**
 * Helper macro for declaring fields.
 */
#define psi_field(name) name { this, #name }

/**
 * Helper macro for declaring the constructor
 * and type registration for PSI-derived classes
 */
#define psi_ctor(_name, _super) \
	public: \
	_name (const Scope &p) : _super(this) { }

#define psi_constraint(_name, _body) \
		Constraint _name {this, #_name, _body};

#define psi_action_ctor(_name) \
		psi_ctor(_name, Action)

#define psi_component_ctor(_name) \
		psi_ctor(_name, Component)

#define psi_package_ctor(_name) \
		psi_ctor(_name, Package)

#define psi_struct_ctor(_name) \
		psi_ctor(_name, Struct)

#endif /* End PSI_HAVE_CXX_11 */

/**
 * Helper macro to register a global namespace type
 */
#define psi_global_type(_name) \
		TypeDecl<_name>		_##_name##_t

#ifdef PSI_HAVE_CXX_11
/**
 * Helper macro to register a non-global namespace type
 */
#define psi_type(_name) \
		TypeDecl<_name>		_##_name##_t {this}

#endif /* End PSI_HAVE_CXX_11 */

#define psi_typeid(T) \
	(*TypeDecl<T>::type_id())

#endif /* INCLUDED_PSI_MACROS_H */
