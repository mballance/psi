/*
 * Exec.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXEC_H_
#define SRC_STATIC_EXEC_H_
#include <string>
#include "IConstructorContext.h"

namespace psi {

class ImportCall;
class Exec {

	public:
		enum Kind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};
		enum Type {
			Null,
			TargetTemplate,
			Native
		};

	public:

		Exec();

		Exec(
			Exec::Kind 				kind,
			IConstructorContext		*p,
			const std::string 		&language,
			const std::string 		&content);

		Exec(
			Exec::Kind 				kind,
			IConstructorContext		*p,
			const ImportCall		&call);

		virtual ~Exec();


		inline Exec::Kind getExecKind() const {
			return m_execKind;
		}

		inline Exec::Type getExecType() const {
			return m_execType;
		}

	private:
		Exec::Type			m_execType;
		Exec::Kind			m_execKind;
		std::string			m_language;
		std::string			m_content;


};

} /* namespace psi */

#endif /* SRC_STATIC_EXEC_H_ */
