/*
 * IInlineExec.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IINLINEEXEC_H_
#define SRC_PSI_API_IINLINEEXEC_H_

#include "api/IObject.h"

namespace psi_api {

class IInlineExec {
public:

	virtual ~IInlineExec() { }

	/**
	 * The 'exec' method is invoked by the evaluation tool to allow
	 * the InlineExec implementation code to get and set values
	 * from the target object
	 */
	virtual void exec(IObject *obj) = 0;

};

}




#endif /* SRC_PSI_API_IINLINEEXEC_H_ */
