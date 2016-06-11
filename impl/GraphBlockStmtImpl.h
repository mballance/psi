/*
 * GraphBlockStmtImpl.h
 *
 *  Created on: Jun 8, 2016
 *      Author: ballance
 */

#ifndef IMPL_GRAPHBLOCKSTMTIMPL_H_
#define IMPL_GRAPHBLOCKSTMTIMPL_H_
#include "api/IGraphBlockStmt.h"

using namespace psi_api;

namespace psi {


class GraphBlockStmtImpl : public IGraphBlockStmt {
public:
	GraphBlockStmtImpl(IGraphBlockStmt::GraphStmtType type);

	virtual ~GraphBlockStmtImpl();

	virtual GraphStmtType getStmtType() const { return m_type; }

	virtual const std::vector<IGraphStmt *> &getStmts() const;

	virtual void add(IGraphStmt *stmt);
private:

	IGraphBlockStmt::GraphStmtType				m_type;
	std::vector<IGraphStmt *>					m_stmts;

};

} /* namespace psi */

#endif /* IMPL_GRAPHBLOCKSTMTIMPL_H_ */
