/*
 * InlineExecUtil.h
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
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_INLINE_EXEC_UTIL_H
#define INCLUDED_INLINE_EXEC_UTIL_H
#include <stdint.h>
#include <vector>
#include "BaseItemImp.h"
#include "api/IModel.h"

using namespace psi_api;

namespace pss {

class InlineExecUtil {
public:
	InlineExecUtil(BaseItemImp *field);

	virtual ~InlineExecUtil();


	uint64_t getBitValue();

	void setBitValue(uint64_t val);

	int64_t getIntValue();

	void setIntValue(int64_t val);

	bool getBoolValue();

	void setBoolValue(bool val);

	void *getChandleValue();

	void setChandleValue(void *val);

	std::string getStringValue();

	void setStringValue(const std::string &val);

private:
	/**
	 * Traverses back the stack from a field reference to
	 * locate the model, object handle, and how deep we are
	 */
	static bool find_model_hndl_level(
			BaseItemImp			*field,
			IModel				*&model,
			psshandle_t			&hndl,
			uint32_t			&level
			);

	bool update_lookup_path();

	void get_hndl_ctxt_field(
			ICallbackContext		*&ctxt,
			psshandle_t				&hndl,
			IField					*&field
			);

private:
	BaseItemImp						*m_field;
	std::vector<IField *>			m_field_path;



};

}

#endif /* INCLUDED_INLINE_EXEC_UTIL_H */
