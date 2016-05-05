/*
 * ILiteral.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ILITERAL_H_
#define SRC_PSI_API_ILITERAL_H_
#include <stdint.h>
#include <string>

#include "api/IExpr.h"

namespace psi_api {

class ILiteral : public IExpr {
public:

	enum LiteralType {
		LiteralInt,
		LiteralBit,
		LiteralBool,
		LiteralString
	};

	virtual ~ILiteral() { }


	virtual LiteralType getLiteralType() const = 0;

	virtual int64_t getInt() const = 0;

	virtual uint64_t getBit() const = 0;

	virtual bool getBool() const = 0;

	virtual const std::string &getString() const = 0;

};

}




#endif /* SRC_PSI_API_ILITERAL_H_ */
