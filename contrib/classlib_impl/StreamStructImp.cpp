/*
 * StreamStruct.cpp
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
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "StreamStructImp.h"
#include "ScopeImp.h"

namespace pss {

StreamStruct::StreamStruct(const Scope &p) :
		Struct(new StreamStructImp(this, p.impl())) { }

StreamStructImp::StreamStructImp(StreamStruct *master, ScopeImp *p) :
		StructImp(master, p, StructImp::Stream) { }

StreamStruct::~StreamStruct() {
	// TODO Auto-generated destructor stub
}

StreamStructImp::~StreamStructImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
