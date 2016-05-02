/*
 * Exec.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXEC_H_
#define SRC_STATIC_EXEC_H_

#include <string>

#include "Type.h"


namespace psi {

class ImportCall;
class Exec : public Type {

	public:
		enum ExecKind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};
		enum ExecType {
			Null,
			TargetTemplate,
			Native
		};

	public:

		Exec(
			ExecKind 				kind,
			Type					*p,
			const std::string 		&language,
			const std::string 		&content);

		Exec(
			ExecKind 				kind,
			Type					*p,
			const ImportCall		&call);

		virtual ~Exec();


		inline ExecKind getExecKind() const {
			return m_execKind;
		}

		inline ExecType getExecType() const {
			return m_execType;
		}

	private:
		ExecType			m_execType;
		ExecKind			m_execKind;
		std::string			m_language;
		std::string			m_content;

};

} /* namespace psi */

#endif /* SRC_STATIC_EXEC_H_ */
