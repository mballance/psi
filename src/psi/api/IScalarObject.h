/*
 * IScalarObject.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ISCALAROBJECT_H_
#define SRC_PSI_API_ISCALAROBJECT_H_

#include "api/IObject.h"

namespace psi_api {

class IScalarObject : public IObject {
public:

	virtual ~IScalarObject() { }

	virtual int64_t getIntValue() = 0;

	virtual void setIntValue(int64_t v) = 0;

	virtual uint64_t getBitValue() = 0;

	virtual void setBitValue(uint64_t v) = 0;

	virtual const std::string &getStringValue() = 0;

	virtual void setStringValue(const std::string &v) = 0;

	virtual bool getBoolValue() = 0;

	virtual void setBoolValue(bool v) = 0;

	virtual void *getChandleValue() = 0;

	virtual void setChandleValue(void *v) = 0;

};

}




#endif /* SRC_PSI_API_ISCALAROBJECT_H_ */
