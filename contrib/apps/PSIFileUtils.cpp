/*
 * PSIFileUtils.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: ballance
 */

#include "PSIFileUtils.h"

namespace psi {

PSIFileUtils::PSIFileUtils() {
	// TODO Auto-generated constructor stub

}

PSIFileUtils::~PSIFileUtils() {
	// TODO Auto-generated destructor stub
}

std::string PSIFileUtils::read(FILE *fp) {
	char tmp[1024];
	size_t sz;
	std::string ret;

	while ((sz = fread(tmp, 1, sizeof(tmp), fp)) > 0) {
		for (uint32_t i=0; i<sz; i++) {
			ret.push_back(tmp[i]);
		}
	}

	return ret;
}

} /* namespace psi */
