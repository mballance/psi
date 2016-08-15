/*
 * ImportFuncImpl.h
 *
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_
#define CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_
#include <string>
#include <vector>
#include "NamedItemImpl.h"
#include "api/IImportFunc.h"
#include "api/IField.h"

namespace psi {

class ImportFuncImpl : public IImportFunc, public virtual NamedItemImpl {
public:
	ImportFuncImpl(
			const std::string				&name,
			IBaseItem						*ret_type,
			const std::vector<IField *>		&parameters);

	virtual ~ImportFuncImpl();

	/**
	 * Method: getType()
	 * Returns the type of this object.
	 */
	virtual ItemType getType() const { return IBaseItem::TypeImportFunc; }

	/**
	 * Create an exact copy of this item
	 */
	virtual IBaseItem *clone() { return 0; }

	virtual IBaseItem *getParent() const { return m_parent; }

	/**
	 * Implementation: not called by user code
	 */
	virtual void setParent(IBaseItem *it) { m_parent = it; }

	IBaseItem *getReturnType() const { return m_ret; }

	const std::vector<IField *> &getParameters() const {
		return m_parameters;
	}


private:
	IBaseItem					*m_parent;
	IBaseItem					*m_ret;
	std::vector<IField *>		m_parameters;
};

} /* namespace psi_api */

#endif /* CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_ */
