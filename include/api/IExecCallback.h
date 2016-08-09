/*
 * IExecCallback.h
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

