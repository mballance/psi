/*
 * Exec.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "Exec.h"
#include "ImportCall.h"

namespace psi {

Exec::Exec() : m_execType(Null) { }

Exec::Exec(
		Exec::Kind 				kind,
		IConstructorContext		*p,
		const std::string 		&language,
		const std::string 		&content) :
			m_execType(TargetTemplate),
			m_execKind(kind),
			m_language(language),
			m_content(content) {
}

Exec::Exec(
		Exec::Kind 				kind,
		IConstructorContext		*p,
		const ImportCall		&call) {

}

Exec::~Exec() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
