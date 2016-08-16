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
#include "BaseItemImpl.h"
#include "NamedItemImpl.h"
#include "api/IImportFunc.h"
#include "api/IField.h"

namespace psi {

class ImportFuncImpl : public IImportFunc,
	public virtual BaseItemImpl,
	public virtual NamedItemImpl {
public:
	ImportFuncImpl(
			const std::string				&name,
			IBaseItem						*ret_type,
			const std::vector<IField *>		&parameters);

	virtual ~ImportFuncImpl();

	IBaseItem *getReturnType() const { return m_ret; }

	const std::vector<IField *> &getParameters() const {
		return m_parameters;
	}


private:
	IBaseItem					*m_ret;
	std::vector<IField *>		m_parameters;
};

} /* namespace psi_api */

#endif /* CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_ */
