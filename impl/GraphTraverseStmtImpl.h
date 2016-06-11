/*
 * GraphTraverseStmtImpl.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef IMPL_GRAPHTRAVERSESTMTIMPL_H_
#define IMPL_GRAPHTRAVERSESTMTIMPL_H_
#include "api/IGraphTraverseStmt.h"

using namespace psi_api;

namespace psi {

class GraphTraverseStmtImpl: public IGraphTraverseStmt {
public:
	GraphTraverseStmtImpl(IFieldRef *action, IConstraint *c);

	virtual ~GraphTraverseStmtImpl();

	virtual GraphStmtType getStmtType() const {
		return GraphStmt_Traverse;
	}

	virtual IFieldRef *getAction() const {
		return m_action;
	}

	virtual IConstraint *getWith() const {
		return m_constraint;
	}

private:

	IFieldRef					*m_action;
	IConstraint					*m_constraint;

};

} /* namespace psi */

#endif /* IMPL_GRAPHTRAVERSESTMTIMPL_H_ */
