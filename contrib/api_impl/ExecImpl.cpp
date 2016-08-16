/*
 * ExecImpl.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#include "../api_impl/ExecImpl.h"

namespace psi {

ExecImpl::ExecImpl(
		ExecKind			kind,
		const std::string	&language,
		const std::string	&text) :
				BaseItemImpl(IBaseItem::TypeExec),
				m_execKind(kind), m_execType(IExec::TargetTemplate),
				m_language(language), m_targetTemplate(text),
				m_inlineExec(0), m_stmts(0) { }

ExecImpl::ExecImpl(
		ExecKind			kind,
		IExecCallback		*exec) :
				BaseItemImpl(IBaseItem::TypeExec),
				m_execKind(kind), m_execType(IExec::Inline),
				m_inlineExec(exec), m_stmts(0) { }

ExecImpl::ExecImpl(
		ExecKind						kind,
		const std::vector<IExecStmt *>	&stmts) :
				BaseItemImpl(IBaseItem::TypeExec),
				m_execKind(kind), m_execType(IExec::Native),
				m_inlineExec(0), m_stmts(stmts) { }

ExecImpl::~ExecImpl() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
