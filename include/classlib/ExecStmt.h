/*
 * ExecStmt.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_CLASSLIB_EXECSTMT_H_
#define INCLUDE_CLASSLIB_EXECSTMT_H_

namespace pss {

class ExecStmtImp;
class FieldItem;
class ExecStmt {
public:
	friend ExecStmtImp;
	friend FieldItem;

	ExecStmt(const ExecStmt &rhs);

	virtual ~ExecStmt();

	ExecStmtImp *imp() const;

protected:
	ExecStmt(ExecStmtImp *imp);

private:
	ExecStmtImp			*m_imp;

};


}




#endif /* INCLUDE_CLASSLIB_EXECSTMT_H_ */
