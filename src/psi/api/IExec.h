/*
 * IExec.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IEXEC_H_
#define SRC_PSI_API_IEXEC_H_
#include <string>
#include "api/IInlineExec.h"
#include "api/IExpr.h"

namespace psi_api {

class IExec : public IBaseItem {
public:

	enum ExecKind {
		Declaration,
		Body,
		PreSolve,
		PostSolve
	};

	enum ExecType {
		TargetTemplate,
		Native,
		Inline
	};

public:

	virtual ~IExec() { }

	virtual ExecKind getExecKind() = 0;

	virtual ExecType getExecType() = 0;

	/**
	 * Returns the target-template string for
	 * exec type TargetTemplate
	 */
	virtual const std::string &getTargetTemplate() = 0;

	/**
	 * Returns the inline-exec closure for exec type Inline
	 */
	virtual IInlineExec *getInlineExec() = 0;

	/**
	 * Returns the native-exec statement list
	 */
	virtual IExpr *getStmts() = 0;

};
}



#endif /* SRC_PSI_API_IEXEC_H_ */
