/*
 * GraphRepeatStmtImpl.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef IMPL_GRAPHREPEATSTMTIMPL_H_
#define IMPL_GRAPHREPEATSTMTIMPL_H_
#include "api/IGraphRepeatStmt.h"

using namespace psi_api;

namespace psi {

class GraphRepeatStmtImpl: public IGraphRepeatStmt {
public:
	GraphRepeatStmtImpl(RepeatType type, IExpr *expr, IGraphStmt *body);

	virtual ~GraphRepeatStmtImpl();

	virtual GraphStmtType getStmtType() const { return GraphStmt_Repeat; }

	virtual RepeatType getRepeatType() const { return m_type; }

	virtual IExpr *getCond() { return m_cond; }

	virtual IGraphStmt *getBody() { return m_body; }

private:
	RepeatType				m_type;
	IExpr					*m_cond;
	IGraphStmt				*m_body;
};


} /* namespace psi */

#endif /* IMPL_GRAPHREPEATSTMTIMPL_H_ */
