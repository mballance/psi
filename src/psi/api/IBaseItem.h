/*
 * IBaseItem.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_API_IBASEITEM_H_
#define SRC_API_IBASEITEM_H_

namespace psi_api {

	/**
	 * Class: IBaseItem
	 *
	 * Common base API to PSI objects
	 */
	class IBaseItem {

	public:

		enum ItemType {
			TypeAction,
			TypeComponent,
			TypeConstraint,
			TypeField,
			TypeImport,
			TypeExec,
			TypeExtendAction,
			TypeExtendComponent,
			TypeExtendStruct,
			TypeGraphStmt,
			TypeModel,
			TypePackage,
			TypeScalar,
			TypeStruct,
			TypeSymbol
		};

		public:
			virtual ~IBaseItem() { }

			/**
			 * Method: getType()
			 * Returns the type of this object.
			 */
			virtual ItemType getType() const = 0;

			/**
			 * Create an exact copy of this item
			 */
			virtual IBaseItem *clone() = 0;

			virtual IBaseItem *getParent() const = 0;

			/**
			 * Implementation: not called by user code
			 */
			virtual void setParent(IBaseItem *it) = 0;
	};


}




#endif /* SRC_API_IBASEITEM_H_ */
