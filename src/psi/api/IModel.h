/*
 * IModel.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IMODEL_H_
#define SRC_PROGRAMMATIC_IMODEL_H_
#include <vector>
#include <string>

#include "api/IAction.h"
#include "api/IBaseItem.h"
#include "api/IBinaryExpr.h"
#include "api/IBitType.h"
#include "api/IComponent.h"
#include "api/IConstraint.h"
#include "api/IConstraintBlock.h"
#include "api/IConstraintIf.h"
#include "api/ILiteral.h"
#include "api/IIntType.h"
#include "api/IPackage.h"
#include "api/IScopeItem.h"
#include "api/IStruct.h"

namespace psi {

	class IModel : public IScopeItem {
		public:

			virtual ~IModel() { }

//			virtual const std::vector<IPackage*> &getPackages() = 0;

			virtual IPackage *getGlobalPackage() = 0;

			virtual IPackage *findPackage(const std::string &name, bool create=false) = 0;

			/**
			 * Data Types
			 */

//			virtual IBitType *mkBitType(uint32_t msb=0, uint32_t lsb=0) = 0;
//
//			virtual IIntType *mkIntType(uint32_t msb=31, uint32_t lsb=0) = 0;
//
//			// TODO: String, Bool types
//
//			/**
//			 * Action
//			 */
//			virtual IAction *mkAction(const std::string &name, IAction *super_type) = 0;

			virtual IComponent *mkComponent(const std::string &name) = 0;

			virtual IStruct *mkStruct(
					const std::string 		&name,
					IStruct::StructType		t,
					IStruct 				*super_type) = 0;

			virtual IBinaryExpr *mkBinExpr(
					IExpr 					*lhs,
					IBinaryExpr::BinOpType	op,
					IExpr 					*rhs) = 0;

			virtual ILiteral *mkIntLiteral(int64_t v) = 0;

			virtual ILiteral *mkBitLiteral(uint64_t v) = 0;

			virtual ILiteral *mkBoolLiteral(bool v) = 0;

			virtual ILiteral *mkStringLiteral(const std::string &v) = 0;

			virtual IConstraintBlock *mkConstraintBlock(const std::string &name) = 0;

			virtual IConstraintIf *mkConstraintIf(
					IExpr 			*cond,
					IConstraint 	*true_c,
					IConstraint 	*false_c) = 0;

	};

}



#endif /* SRC_PROGRAMMATIC_IMODEL_H_ */
