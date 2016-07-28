/*
 * Scope.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_IMP_H
#define INCLUDED_SCOPE_IMP_H
#include <string>
#include <vector>
#include <typeinfo>

#include "classlib/Scope.h"

namespace psi {

class BaseItemImp;
class Scope;
class ScopeImp {
public:
	friend Scope;
	ScopeImp(
			Scope 					*master,
			const std::type_info	*type,
			BaseItemImp 			*ctxt,
			bool					in_field_decl,
			const std::string		&name);

	virtual ~ScopeImp();

	BaseItemImp *parent() const;

	BaseItemImp *ctxt() const { return m_ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	bool in_field_decl() const { return m_in_field_decl; }

private:

	void enter();

	void leave();

private:
	Scope					*m_master;
	bool					m_in_field_decl;
	BaseItemImp				*m_ctxt;
	const std::type_info	*m_type;
	std::string				m_name;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
