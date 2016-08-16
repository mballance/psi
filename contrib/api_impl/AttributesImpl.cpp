/*
 * AttributesImpl.cpp
 *
 *  Created on: Aug 16, 2016
 *      Author: ballance
 */

#include "AttributesImpl.h"

namespace psi {

AttributesImpl::AttributesImpl() {
	// TODO Auto-generated constructor stub

}

AttributesImpl::~AttributesImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &AttributesImpl::getAttribute(const std::string &key) {
	std::map<std::string,std::string>::iterator it;

	if ((it=m_attr.find(key)) != m_attr.end()) {
		return it->second;
	} else {
		return m_null_attr;
	}
}

void AttributesImpl::getAttributes(std::vector<std::string> &keys) {
	std::map<std::string,std::string>::iterator it;
	keys.clear();

	for (it=m_attr.begin(); it!=m_attr.end(); it++) {
		keys.push_back(it->first);
	}
}

bool AttributesImpl::hasAttribute(const std::string &key) {
	return (m_attr.find(key) != m_attr.end());
}

void AttributesImpl::setAttribute(const std::string &key, const std::string &val) {
	std::map<std::string,std::string>::iterator it;

	it=m_attr.find(key);

	if (it != m_attr.end()) {
		m_attr.erase(it);
	}

	m_attr[key] = val;
}

void AttributesImpl::clearAttribute(const std::string &key) {
	std::map<std::string,std::string>::iterator it;

	it=m_attr.find(key);

	if (it != m_attr.end()) {
		m_attr.erase(it);
	}
}

std::string AttributesImpl::m_null_attr;

} /* namespace psi */
