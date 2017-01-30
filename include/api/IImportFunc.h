/*
 * IImportFunc.h
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
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IMPORT_FUNC_H
#define INCLUDED_IMPORT_FUNC_H
#include <vector>
#include "api/IBaseItem.h"
#include "api/IExecCallback.h"
#include "api/INamedItem.h"
#include "api/IField.h"

namespace psi_api {

class IImportFunc : public virtual IBaseItem, public virtual INamedItem {
public:

	virtual ~IImportFunc() { }

	virtual IField *getReturn() const = 0;

	virtual const std::vector<IField *> &getParameters() const = 0;

	virtual void setCallback(IExecCallback *cb) = 0;

	virtual IExecCallback *getCallback() = 0;

};


}



#endif /* INCLUDE_API_IIMPORTFUNC_H_ */
