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

#define psi_action_ctor(_name) \
		psi_ctor(_name, Action)

#define psi_component_ctor(_name) \
		psi_ctor(_name, Component)

#define psi_package_ctor(_name) \
		psi_ctor(_name, Package)

#define psi_struct_ctor(_name) \
		psi_ctor(_name, Struct)

#define psi_state_ctor(_name) \
		psi_ctor(_name, StateStruct)

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
