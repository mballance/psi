/*
 * ExecImpl.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#include "ExecImpl.h"

namespace psi {

ExecImpl::ExecImpl(
		ExecKind			kind,
		const std::string	text) :
				m_execKind(kind), m_execType(IExec::TargetTemplate),
				m_inlineExec(0), m_stmts(0) { }

ExecImpl::ExecImpl(
		ExecKind			kind,
		IInlineExec			*exec) :
				m_execKind(kind), m_execType(IExec::Inline),
				m_inlineExec(exec), m_stmts(0) { }

ExecImpl::ExecImpl(
		ExecKind			kind,
		IExpr				*stmts) :
				m_execKind(kind), m_execType(IExec::Native),
				m_inlineExec(0), m_stmts(stmts) { }

ExecImpl::~ExecImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
