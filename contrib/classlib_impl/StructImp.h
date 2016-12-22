/*
 * pss_struct.h
 *
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

#ifndef INCLUDED_STRUCT_IMP_H
#define INCLUDED_STRUCT_IMP_H
#include <string>

#include "classlib/pss_struct.h"
#include "NamedBaseItemImp.h"
#include "TypePathImp.h"
#include "FieldItemImp.h"
#include "api/IExecCallback.h"
#include "api/IModel.h"

using namespace psi_api;

namespace pss {


class StructImp : public NamedBaseItemImp {
public:

	enum StructType {
		Base,
		Memory,
		State,
		Stream,
		Resource
	};

public:

	StructImp(pss_struct *master, ScopeImp *p, StructType t=Base);

	virtual ~StructImp();

	const TypePathImp &getSuperType() const;

	StructType getStructType() const;

	virtual void inline_exec_pre(IModel *model, psshandle_t hndl);

	virtual void pre_solve();
	virtual void post_solve();

	virtual void inline_exec_post();

	IModel *getModel() const { return m_model; }

	psshandle_t getHandle() const { return m_hndl; }

	virtual const std::string &getName() const;

	attr_item &getField() const { return *m_field; }

private:
	StructType				m_struct_type;
	TypePathImp				m_super_type;
	IModel					*m_model;
	psshandle_t				m_hndl;
	attr_item				*m_field;

};

} /* namespace pss */

#endif /* INCLUDED_STRUCT_IMP_H */
