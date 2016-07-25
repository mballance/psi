/*
 * IBindPath.h
 *
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IBINDPATH_H_
#define SRC_PSI_API_IBINDPATH_H_
#include <vector>

namespace psi_api {

class IBaseItem;
class IBindPath {
public:
	virtual ~IBindPath() { }

	virtual const std::vector<IBaseItem *> &getPath() const = 0;


};

}



#endif /* SRC_PSI_API_IBINDPATH_H_ */
