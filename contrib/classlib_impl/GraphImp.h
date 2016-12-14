/*
 * graph.h
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
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_GRAPH_IMP_H
#define INCLUDED_GRAPH_IMP_H
#include "classlib/graph.h"
#include "BaseItemImp.h"

namespace pss {

class GraphImp : public BaseItemImp {

	public:
		GraphImp(graph *master, BaseItem *p, const ExprList &seq);

		virtual ~GraphImp();

		ExprList &getSequence() { return m_seq; }

	private:
		ExprList				m_seq;
};

} /* namespace pss */

#endif /* GRAPH_H_ */
