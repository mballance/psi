/*
 * ExprCoreList.cpp
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "ExprCoreList.h"
#include "ExprImp.h"

namespace pss {

ExprCoreList::ExprCoreList() : ExprCore(ExprImp::List) {

}

ExprCoreList::ExprCoreList(const Expr &e) : ExprCore(ExprImp::List) {
	add(e);
}

ExprCoreList::ExprCoreList(const Expr &e1, const Expr &e2) : ExprCore(ExprImp::List) {
	add(e1);
	add(e2);
}

ExprCoreList::~ExprCoreList() {
	// TODO Auto-generated destructor stub
}

void ExprCoreList::add(const Expr &e) {
	m_exprList.push_back(e.imp());
}

void ExprCoreList::add(const ExprImp &e) {
	m_exprList.push_back(e);
}

} /* namespace pss */
