/*
 * Exec.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "classlib/Exec.h"

#include "classlib/ImportCall.h"

namespace psi {

//Exec::Exec() : m_execType(Null) { }

Exec::Exec(
		ExecKind 				kind,
		Type					*p,
		const std::string 		&language,
		const std::string 		&content) :
			Type(Type::TypeExec, p),
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) {
}

Exec::Exec(
		ExecKind 				kind,
		Type					*p,
		const ImportCall		&call) :
			Type(Type::TypeExec, p),
			m_execType(Native),
			m_execKind(kind),
			m_language(""),
			m_content("") {
	// TODO: save call information
}

Exec::~Exec() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
