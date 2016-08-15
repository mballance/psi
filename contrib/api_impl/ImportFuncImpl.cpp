/*
 * ImportFuncImpl.cpp
 *
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#include "ImportFuncImpl.h"

namespace psi {

ImportFuncImpl::ImportFuncImpl(
		const std::string				&name,
		IBaseItem						*ret,
		const std::vector<IField *>		&parameters) :
			NamedItemImpl(name, IBaseItem::TypeImportFunc) {
	// TODO Auto-generated constructor stub

}

ImportFuncImpl::~ImportFuncImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi_api */
