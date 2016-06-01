/*
 * ExecImpl.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef IMPL_EXECIMPL_H_
#define IMPL_EXECIMPL_H_
#include "api/IExec.h"

using namespace psi_api;

namespace psi {

class ExecImpl : public IExec {
public:
	ExecImpl(
			ExecKind			kind,
			const std::string	text);

	ExecImpl(
			ExecKind			kind,
			IInlineExec			*exec);

	ExecImpl(
			ExecKind			kind,
			IExpr				*stmts);

	virtual ~ExecImpl();

	virtual ItemType getType() const { return TypeExec; }

	virtual ExecKind getExecKind() { return m_execKind; }

	virtual ExecType getExecType() { return m_execType; }

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
	virtual IInlineExec *getInlineExec() { return m_inlineExec; }

	/**
	 * Returns the native-exec statement list
	 */
	virtual IExpr *getStmts() { return m_stmts; }

private:
	ExecKind					m_execKind;
	ExecType					m_execType;
	std::string					m_targetTemplate;
	IInlineExec					*m_inlineExec;
	IExpr						*m_stmts;

};

} /* namespace psi */

#endif /* IMPL_EXECIMPL_H_ */
