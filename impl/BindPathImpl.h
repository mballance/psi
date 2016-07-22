/*
 * BindPathImpl.h
 *
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef IMPL_BINDPATHIMPL_H_
#define IMPL_BINDPATHIMPL_H_
#include "api/IBindPath.h"

using namespace psi_api;

namespace psi {

class BindPathImpl: public IBindPath {
public:
	BindPathImpl(const std::vector<IBaseItem *> &path);

	virtual ~BindPathImpl();

	virtual const std::vector<IBaseItem *> &getPath() const { return m_path; }

private:
	std::vector<IBaseItem *>			m_path;

};

} /* namespace psi */

#endif /* IMPL_BINDPATHIMPL_H_ */
