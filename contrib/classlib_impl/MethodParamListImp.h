/*
 * MethodParamListImp.h
 *
 *  Created on: Aug 26, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_
#include "classlib/MethodParamList.h"

namespace pss {

class FieldItemImp;
class MethodParamListImp {
public:
	MethodParamListImp(MethodParamList	*master);

	virtual ~MethodParamListImp();

	void add(const FieldItem &rhs);

	const std::vector<FieldItem> &parameters() const {
		return m_parameters;
	}

	void inc_refcnt();

	void dec_refcnt();

private:
	std::vector<FieldItem>			m_parameters;
	uint32_t						m_refcnt;

};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_ */
