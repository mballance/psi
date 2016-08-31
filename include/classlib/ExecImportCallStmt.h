/*
 * ExecImportCallStmt.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_
#define INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_

#include "classlib/ExecStmt.h"
#include "classlib/ExprList.h"

namespace pss {

class ImportFunc;
class ExecImportCallStmt : public ExecStmt {
public:
	friend ImportFunc;

private:
	ExecImportCallStmt(const ImportFunc &f, const ExprList &plist);

};

}




#endif /* INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_ */
