/*
 * MethodParam.h
 *
 *  Created on: Aug 26, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_CLASSLIB_METHODPARAM_H_
#define INCLUDE_CLASSLIB_METHODPARAM_H_
#include <string>

namespace pss {

class MethodParamImp;
class MethodParamList;
class BaseItem;
class MethodParam {
	friend class MethodParamImp;
	friend class MethodParamList;
public:
	enum Dir {
		In,
		Out,
		InOut
	};

	virtual ~MethodParam();

protected:
	MethodParam(
			const std::string 	&name,
			Dir					dir,
			BaseItem			*type);

private:
	MethodParamImp				*m_imp;

};

}




#endif /* INCLUDE_CLASSLIB_METHODPARAM_H_ */
