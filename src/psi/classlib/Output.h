/*
 * Output.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
#include <stdio.h>

#include "classlib/FieldItem.h"
#include "classlib/TypeDecl.h"

namespace psi {

// TODO: may need an OutputBase class to enable binding
template <class T> class Output : public FieldItem, public T {

	public:
		Output(BaseItem *p, const std::string &name) : FieldItem(p, name), T(Scope::ScopeType_FieldDecl) {
			setAttr(FieldItem::AttrOutput);
			setDataType(TypeDecl<T>::type_id());
		}

		virtual ~Output() { }
};

} /* namespace psi */

#endif /* OUTPUT_H_ */
