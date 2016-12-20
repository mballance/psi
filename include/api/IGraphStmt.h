/*
 * IGraphStmt.h
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
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHSTMT_H_
#define SRC_PSI_API_IGRAPHSTMT_H_

namespace psi_api {

class IGraphStmt {
public:
	enum GraphStmtType {
		/*! graph block statement. Object is of type IGraphBlockStmt. */
		GraphStmt_Block,
		/*! graph if/else statement. Object is of type IGraphIfElseStmt.
		 * Used for both top-level if/else and for if-gated pss_select statement */
		GraphStmt_IfElse,
		/*! graph parallel statement. Object is of type IGraphBlockStmt */
		GraphStmt_Parallel,
		/*! graph schedule statement. Object is of type IGraphBlockStmt */
		GraphStmt_Schedule,
		//! graph pss_select statement. Object is of type IGraphBlockStmt
		GraphStmt_Select,
		//! graph repeat, repeat while, or repeat ... while statement.
		//! Object is of type IGraphRepeatStmt
		GraphStmt_Repeat,

		/*! graph action-traversal statement */
		GraphStmt_Traverse
	};

public:
	virtual ~IGraphStmt() { }

	virtual GraphStmtType getStmtType() const = 0;

};
}




#endif /* SRC_PSI_API_IGRAPHSTMT_H_ */
