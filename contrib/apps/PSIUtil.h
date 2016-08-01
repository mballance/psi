/*
 * PSIUtil.h
 *
 *  Created on: May 17, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_UTIL_PSIUTIL_H_
#define SRC_PSI_UTIL_PSIUTIL_H_
#include "../../include/psi_api.h"

using namespace psi_api;

namespace psi {
namespace apps {

class PSIUtil {
public:
	PSIUtil();

	virtual ~PSIUtil();

	static IScopeItem *toScopeItem(IBaseItem *it);

	static INamedItem *toNamedItem(IBaseItem *it);
};

}
}

#endif /* SRC_PSI_UTIL_PSIUTIL_H_ */
