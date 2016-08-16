/*
 * ExecImpl.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef IMPL_EXECIMPL_H_
#define IMPL_EXECIMPL_H_
#include "api/IExec.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ExecImpl :
		public virtual IExec,
		public virtual BaseItemImpl {
public:
	ExecImpl(
			ExecKind			kind,
			const std::string	&language,
			const std::string	&text);

	ExecImpl(
			ExecKind			kind,
			IExecCallback		*exec);

	ExecImpl(
			ExecKind						kind,
			const std::vector<IExecStmt *>	&stmts);

	virtual ~ExecImpl();

	virtual ExecKind getExecKind() { return m_execKind; }

	virtual ExecType getExecType() { return m_execType; }

	virtual const std::string &getLanguage() const { return m_language; }

	/**
	 * Returns the target-template string for
	 * exec type TargetTemplate
	 */
	virtual const std::string &getTargetTemplate() {
		return m_targetTemplate;
	}

	/**
	 * Returns the inline-exec closure for exec type Inline
	 */
	virtual IExecCallback *getInlineExec() { return m_inlineExec; }

	/**
	 * Returns the native-exec statement list
	 */
	virtual const std::vector<IExecStmt *> &getStmts() { return m_stmts; }

private:
	ExecKind					m_execKind;
	ExecType					m_execType;
	std::string					m_language;
	std::string					m_targetTemplate;
	IExecCallback				*m_inlineExec;
	std::vector<IExecStmt *>	m_stmts;

};

} /* namespace psi */

#endif /* IMPL_EXECIMPL_H_ */
