/*
 * ISymbol.h
 *
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ISYMBOL_H_
#define SRC_PSI_API_ISYMBOL_H_
#include <string>
#include "api/IBaseItem.h"

namespace psi_api {

class ISymbol : public IBaseItem {
public:
	virtual ~ISymbol() { }

	virtual const std::string &getName() const = 0;

	virtual IGraphStmt *getBody() const = 0;

};
}




#endif /* SRC_PSI_API_ISYMBOL_H_ */
