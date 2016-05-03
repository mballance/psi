/*
 * ModelImpl.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_MODELIMPL_H_
#define IMPL_MODELIMPL_H_
#include "PackageImpl.h"
#include "IModel.h"
#include "ScopeItemImpl.h"

namespace psi {

class ModelImpl: public virtual IModel, public ScopeItemImpl {

	public:
		ModelImpl();

		virtual ~ModelImpl();

//		virtual const std::vector<IPackage*> &getPackages();

		virtual const std::vector<IBaseItem *> &getItems() const;

		virtual IPackage *getGlobalPackage();

		virtual IPackage *findPackage(const std::string &name, bool create=false);

		/**
		 * Data Types
		 */

//		virtual IBitType *mkBitType(uint32_t msb=0, uint32_t lsb=0);
//
//		virtual IIntType *mkIntType(uint32_t msb=31, uint32_t lsb=0);
//
//		// TODO: String, Bool types
//
//		/**
//		 * Action
//		 */
//		virtual IAction *mkAction(const std::string &name, IAction *super_type);


	private:
		PackageImpl					m_global_pkg;
		std::vector<IBaseItem *>	m_children;
//		std::vector<IPackage *>		m_packages;

};

} /* namespace psi */

#endif /* IMPL_MODELIMPL_H_ */
