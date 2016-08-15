/*
 * IImportFunc.h
 *
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IMPORT_FUNC_H
#define INCLUDED_IMPORT_FUNC_H
#include <vector>
#include "api/IBaseItem.h"
#include "api/INamedItem.h"
#include "api/IField.h"

namespace psi_api {

class IImportFunc : public IBaseItem, public virtual INamedItem {
public:

	virtual ~IImportFunc() { }

	virtual IBaseItem *getReturnType() const = 0;

	virtual const std::vector<IField *> &getParameters() const = 0;

};


}



#endif /* INCLUDE_API_IIMPORTFUNC_H_ */
