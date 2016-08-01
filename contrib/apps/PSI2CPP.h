/*
 * PSI2CPP.h
 *
 *  Created on: Jul 18, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSI2CPP_H_
#define SRC_APPS_PSI2CPP_H_

#include "PSI2StringProcessor.h"

namespace psi {
namespace apps {

class PSI2CPP: public apps::PSI2StringProcessor {
public:
	PSI2CPP();
	virtual ~PSI2CPP();
};

} /* namespace apps */
} /* namespace psi */

#endif /* SRC_APPS_PSI2CPP_H_ */
