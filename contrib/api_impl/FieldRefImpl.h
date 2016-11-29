/*
 * FieldRefImpl.h
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
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef IMPL_FIELDREFIMPL_H_
#define IMPL_FIELDREFIMPL_H_
#include "api/IField.h"
#include "api/IFieldRef.h"

using namespace psi_api;

namespace psi {

class FieldRefImpl: public IFieldRef {
public:
	FieldRefImpl(const std::vector<IField *> &field_path);

#ifdef PSS_HAVE_CXX_11
	FieldRefImpl(std::initializer_list<IField *> field_path) :
		FieldRefImpl(std::vector<IField *>(field_path)) { }
#endif

	FieldRefImpl(IField *field_path);

	virtual ~FieldRefImpl();

	virtual ExprType getType() const { return IExpr::ExprType_FieldRef; }

	virtual const std::vector<IField *> &getFieldPath() const { return m_field_path; }

private:
	std::vector<IField *>	m_field_path;

};

} /* namespace psi */

#endif /* IMPL_FIELDREFIMPL_H_ */
