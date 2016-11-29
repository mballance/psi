/*
 * Graph.h
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

#ifndef INCLUDED_GRAPH_H
#define INCLUDED_GRAPH_H
#include "classlib/BaseItem.h"
#include "classlib/ExprList.h"

namespace pss {

class Graph : public BaseItem {

	public:
		Graph(BaseItem *p, const ExprList &seq);

#ifdef PSS_HAVE_CXX_11
		template<typename... I> Graph(BaseItem *p, const I&... items) :
				Graph(p, ExprList::mklist(items...)) { }
#endif

		virtual ~Graph();

};

} /* namespace pss */

#endif /* GRAPH_H_ */
