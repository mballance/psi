/*
 * IField.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IFIELD_H_
#define SRC_PSI_API_IFIELD_H_
#include <stdint.h>
#include <string>
#include "api/IBaseItem.h"

namespace psi_api {

class IField : public IBaseItem {
public:

	enum FieldAttr {
		FieldAttr_None = 0,
		FieldAttr_Rand,
		FieldAttr_Input,
		FieldAttr_Lock,
		FieldAttr_Output,
		FieldAttr_Pool,
		FieldAttr_Share
	};

public:


	virtual ~IField() { }

	virtual const std::string &getName() const = 0;

	virtual IBaseItem *getDataType() const = 0;

	virtual FieldAttr getAttr() const = 0;

};


}




#endif /* SRC_PSI_API_IFIELD_H_ */
