/*
 * GraphBlockStmtImpl.h
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

	void insert(std::vector<IGraphStmt *>::iterator it, IGraphStmt *stmt);

private:

	IGraphBlockStmt::GraphStmtType				m_type;
	std::vector<IGraphStmt *>					m_stmts;

};

} /* namespace psi */

#endif /* IMPL_GRAPHBLOCKSTMTIMPL_H_ */
