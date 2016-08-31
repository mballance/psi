/*
 * ExecImportCallStmtImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_

#include "ExecStmtImp.h"
#include "classlib/ImportFunc.h"
#include "classlib/ExprList.h"
#include "ImportFuncImp.h"

namespace pss {

class ExecImportCallStmtImp: public ExecStmtImp {
public:
	ExecImportCallStmtImp(
			const ImportFunc		&imp,
			const ExprList			&plist
			);

	virtual ~ExecImportCallStmtImp();

	ImportFuncImp *getFunc() const { return static_cast<ImportFuncImp *>(m_imp.impl()); }

	ExprList &getParameterList() { return m_plist; }

private:
	ImportFunc						m_imp;
	ExprList						m_plist;

};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_ */
