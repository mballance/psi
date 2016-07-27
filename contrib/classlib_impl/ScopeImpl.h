/*
 * Scope.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_IMPL_H
#define INCLUDED_SCOPE_IMPL_H
#include <string>
#include <vector>
#include <typeinfo>

#include "classlib/Scope.h"

namespace psi {

class BaseItemImpl;
class Scope;
class ScopeImpl {
public:
	ScopeImpl(
			Scope 				*master,
			std::type_info 		*type,
			BaseItemImpl 		*ctxt,
			bool				in_field_decl,
			const std::string	&name);

	virtual ~ScopeImpl();

	BaseItemImpl *parent() const;

	BaseItemImpl *ctxt() const { return m_ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	bool in_field_decl() const { return m_in_field_decl; }

private:

	void enter();

	void leave();

private:
	Scope					*m_master;
	bool					m_in_field_decl;
	BaseItemImpl			*m_ctxt;
	const std::type_info	*m_type;
	std::string				m_name;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
