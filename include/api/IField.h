/*
 * IField.h
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
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IFIELD_H_
#define SRC_PSI_API_IFIELD_H_
#include <stdint.h>
#include <string>
#include "api/IBaseItem.h"
#include "api/IFieldRef.h"
#include "api/INamedItem.h"

namespace psi_api {

class IField :
		public virtual IBaseItem,
		public virtual INamedItem {
public:

	enum FieldAttr {
		FieldAttr_None = 0,
		FieldAttr_Rand,
		FieldAttr_Input,
		FieldAttr_Inout,
		FieldAttr_Lock,
		FieldAttr_Output,
		FieldAttr_Pool,
		FieldAttr_Share
	};

public:


	virtual ~IField() { }

	virtual IBaseItem *getDataType() const = 0;

	virtual void setDataType(IBaseItem *type) = 0;

	virtual FieldAttr getAttr() const = 0;

	virtual IExpr *getArrayDim() const = 0;

};


}




#endif /* SRC_PSI_API_IFIELD_H_ */
