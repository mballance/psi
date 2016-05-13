/*
 * StructImpl.h
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
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef IMPL_STRUCTIMPL_H_
#define IMPL_STRUCTIMPL_H_
#include <string>
#include <vector>

#include "api/IStruct.h"

using namespace psi_api;

namespace psi {

class StructImpl: public IStruct {
public:

	StructImpl(const std::string &name, psi_api::IStruct::StructType t, IStruct *super_type);

	virtual ~StructImpl();

	virtual IBaseItem::ItemType getType() const {
		return IBaseItem::TypeStruct;
	}

	virtual IStruct *getSuperType() const { return m_super_type; }

	virtual const std::string &getName() const;

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return m_parent; }

	void setParent(IBaseItem *p) { m_parent = p; }

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void add(IBaseItem *it);

	virtual psi_api::IStruct::StructType getStructType() const {
		return m_struct_type;
	}

private:
	IBaseItem						*m_parent;
	std::string						m_name;
	psi_api::IStruct::StructType	m_struct_type;
	std::vector<IBaseItem *>		m_children;
	IStruct							*m_super_type;

};

} /* namespace psi */

#endif /* IMPL_STRUCTIMPL_H_ */
