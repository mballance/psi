/*
 * AttributesImpl.h
 *
 *  Created on: Aug 16, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_
#define CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_
#include "api/IAttributes.h"
#include <map>
#include <string>

using namespace psi_api;

namespace psi {

class AttributesImpl: public virtual IAttributes {
public:
	AttributesImpl();

	virtual ~AttributesImpl();

	virtual const std::string &getAttribute(const std::string &key);

	virtual void getAttributes(std::vector<std::string> &keys);

	virtual bool hasAttribute(const std::string &key);

	virtual void setAttribute(const std::string &key, const std::string &val);

	virtual void clearAttribute(const std::string &key);

private:
	std::map<std::string,std::string>	m_attr;
	static std::string					m_null_attr;


};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_ */
