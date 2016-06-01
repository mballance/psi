/*
 * IBind.h
 *
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IBIND_H_
#define SRC_PSI_API_IBIND_H_
#include "api/IBaseItem.h"

namespace psi_api {

class IBind : public IBaseItem {
public:

	virtual ~IBind() { }

	virtual const std::vector<IBaseItem *> &getTargets() const = 0;


};

}




#endif /* SRC_PSI_API_IBIND_H_ */
