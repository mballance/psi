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
	TypeRgy<_name> type_id {this}; \
	_name (Type *p=0, psi_name name=#_name, \
			_super *super=TypeRgy<_super>::valid()?TypeRgy<_super>::type_id():0) : _super(p, name, super) { }

#endif /* End PSI_HAVE_CXX_11 */

#endif /* INCLUDED_PSI_MACROS_H */
