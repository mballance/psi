/*
 * PSIFileUtils.h
 *
 *  Created on: Sep 13, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_APPS_PSIFILEUTILS_H_
#define CONTRIB_APPS_PSIFILEUTILS_H_
#include <stdio.h>
#include <string>

namespace psi {

class PSIFileUtils {
public:
	PSIFileUtils();

	virtual ~PSIFileUtils();

	static std::string read(FILE *fp);

};

} /* namespace psi */

#endif /* CONTRIB_APPS_PSIFILEUTILS_H_ */
