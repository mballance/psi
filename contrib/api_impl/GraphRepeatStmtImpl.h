/*
 * GraphRepeatStmtImpl.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
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

	virtual void setBody(IGraphStmt *s);

private:
	RepeatType				m_type;
	IExpr					*m_cond;
	IGraphStmt				*m_body;
};


} /* namespace psi */

#endif /* IMPL_GRAPHREPEATSTMTIMPL_H_ */
