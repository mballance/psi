/*
 * ExecImportCallStmtImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecImportCallStmtImp.h"

namespace pss {

ExecImportCallStmt::ExecImportCallStmt(
		const ImportFunc		&imp,
		const ExprList			&plist) : ExecStmt(new ExecImportCallStmtImp(imp, plist)) { }

ExecImportCallStmtImp::ExecImportCallStmtImp(
		const ImportFunc		&imp,
		const ExprList			&plist) :
				ExecStmtImp(StmtType_Call), m_imp(imp), m_plist(plist) { }

ExecImportCallStmtImp::~ExecImportCallStmtImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
