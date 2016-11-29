/*
 * IExecCallback.h
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
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IEXEC_CALLBACK_H
#define INCLUDED_IEXEC_CALLBACK_H

#include "api/ICallbackContext.h"

namespace psi_api {

class IModel;
class IExecCallback {
public:

	virtual ~IExecCallback() { }

	/**
	 * The 'exec' method is invoked by the evaluation tool to allow
	 * the InlineExec implementation code to get and set values
	 * from the target object
	 */
	virtual void exec(
			IModel				*model,
			psshandle_t			instance_h) = 0;

};

}


#endif /* INCLUDED_IEXEC_CALLBACK_H */

