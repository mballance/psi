/*
 * IExtend.h
 *
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IEXTEND_H_
#define SRC_PSI_API_IEXTEND_H_
#include "api/IScopeItem.h"

namespace psi_api {

class IExtend : public IScopeItem {
public:

	enum ExtendType {
		ExtendType_Action,
		ExtendType_Component,
		ExtendType_Struct
	};

	virtual ExtendType getExtendType() const = 0;

	virtual IBaseItem *getTarget() const = 0;


};

}




#endif /* SRC_PSI_API_IEXTEND_H_ */
