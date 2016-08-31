/*
 * IItemFactory.h
 *
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_ITEM_FACTORY_H
#define INCLUDED_ITEM_FACTORY_H
#include <vector>
#include <string>
#include "api/IBinaryExpr.h"
#include "api/IBind.h"
#include "api/IBindPath.h"
#include "api/IComponent.h"
#include "api/IConstraintBlock.h"
#include "api/IConstraintExpr.h"
#include "api/IConstraintIf.h"
#include "api/IExec.h"
#include "api/IExecStmt.h"
#include "api/IExecExprStmt.h"
#include "api/IExecCallStmt.h"
#include "api/IExtend.h"
#include "api/IGraphBlockStmt.h"
#include "api/IGraphRepeatStmt.h"
#include "api/IGraphTraverseStmt.h"
#include "api/ILiteral.h"
#include "api/IScalarType.h"
#include "api/IStruct.h"
#include "api/IConstraintImplies.h"
#include "api/IImportFunc.h"

namespace psi_api {

class IItemFactory {
public:

	virtual ~IItemFactory() { }

	/**
	 * Data Types
	 */

	/**
	 * Creates a scalar type. The msb and lsb parameters are ignored for types
	 * other than Int and Bit
	 */
	virtual IScalarType *mkScalarType(
			IScalarType::ScalarType t,
			uint32_t				msb,
			uint32_t				lsb) = 0;

	/**
	 * Action
	 */
	virtual IAction *mkAction(const std::string &name, IAction *super_type) = 0;

	/**
	 * Creates a new bind statement
	 */
	virtual IBind *mkBind(const std::vector<IBindPath *> &targets) = 0;

	virtual IBindPath *mkBindPath(const std::vector<IBaseItem *> &elems) = 0;


	/**
	 * Create a new component type
	 */
	virtual IComponent *mkComponent(const std::string &name) = 0;

	virtual IExec *mkTargetTemplateExec(
			IExec::ExecKind 		kind,
			const std::string		&language,
			const std::string 		&text) = 0;

	virtual IExec *mkInlineExec(
			IExec::ExecKind 		kind,
			IExecCallback			*exec) = 0;

	virtual IExec *mkNativeExec(
			IExec::ExecKind					kind,
			const std::vector<IExecStmt *>	&stmts) = 0;

	virtual IExecExprStmt *mkExecExprStmt(
			IField					*field,
			IExecStmt::AssignOp		op,
			IExpr					*rhs) = 0;

	virtual IExecCallStmt *mkExecCallStmt(
			IField						*target,
			IExecStmt::AssignOp			op,
			IImportFunc					*func,
			const std::vector<IExpr *>	&parameters) = 0;

	/**
	 * Create a new struct type
	 */
	virtual IStruct *mkStruct(
			const std::string 		&name,
			IStruct::StructType		t,
			IStruct 				*super_type) = 0;

	virtual IExtend *mkExtend(IBaseItem	*target) = 0;

	/**
	 * Create a field for use in declaring the contents of an
	 * action or struct data type
	 */
	virtual IField *mkField(
			const std::string		&name,
			IBaseItem				*field_type,
			IField::FieldAttr		attr,
			IExpr					*array_dim) = 0;

	virtual IBinaryExpr *mkBinExpr(
			IExpr 					*lhs,
			IBinaryExpr::BinOpType	op,
			IExpr 					*rhs) = 0;

	virtual IFieldRef *mkFieldRef(
			const std::vector<IField *>		&field_path) = 0;

	/**
	 * Creates a new block statement. Parallel, Schedule, Select, and
	 * Block statements are all, fundamentally, block statements.
	 * The value of the 'type' parameter can be
	 * GraphStmt_Block, GraphStmt_Parallel, GraphStmt_Schedule, or GraphStmt_Select
	 */
	virtual IGraphBlockStmt *mkGraphBlockStmt(
			IGraphStmt::GraphStmtType type=IGraphStmt::GraphStmt_Block) = 0;

	virtual IGraphTraverseStmt *mkGraphTraverseStmt(
			IFieldRef *action, IConstraint *with_c=0) = 0;

	virtual IGraphRepeatStmt *mkGraphRepeatStmt(
			IGraphRepeatStmt::RepeatType type,
			IExpr *expr, IGraphStmt *body) = 0;

	virtual ILiteral *mkIntLiteral(int64_t v) = 0;

	virtual ILiteral *mkBitLiteral(uint64_t v) = 0;

	virtual ILiteral *mkBoolLiteral(bool v) = 0;

	virtual ILiteral *mkStringLiteral(const std::string &v) = 0;

	/**
	 * Construct a new constraint block. The constraint block is
	 * anonymous if name="". The specified constraint will be
	 * added to the block if it is non-null
	 */
	virtual IConstraintBlock *mkConstraintBlock(
			const std::string 	&name,
			IConstraint			*c=0) = 0;

	/**
	 * Construct a new constraint block, with a list of constraints
	 */
	virtual IConstraintBlock *mkConstraintBlock(
			const std::string 					&name,
			const std::vector<IConstraint *>	&cl) = 0;

	virtual IConstraintExpr *mkConstraintExpr(IExpr *expr) = 0;

	virtual IConstraintIf *mkConstraintIf(
			IExpr 			*cond,
			IConstraint 	*true_c,
			IConstraint 	*false_c) = 0;

	virtual IConstraintImplies *mkConstraintImplies(
			IExpr			*cond,
			IConstraint		*imp) = 0;

	virtual IImportFunc *mkImportFunc(
			const std::string				&name,
			IBaseItem						*ret_type,
			const std::vector<IField *>		&parameters) = 0;

	/**
	 * Clones the specified item using this factory.
	 * Clone is a recursive operation
	 */
	virtual IBaseItem *clone(IBaseItem *item) = 0;
};

}



#endif /* INCLUDE_API_IITEMFACTORY_H_ */
