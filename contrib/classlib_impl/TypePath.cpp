/*
 * TypePath.cpp
 *
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#include "TypePath.h"

namespace psi {

TypePath::TypePath() { }

TypePath::TypePath(const std::vector<std::string> &path) :
	m_path(path) { }

TypePath::TypePath(const std::string &path) {
	m_path.push_back(path);
}

void TypePath::set(const std::vector<std::string> &path) {
	m_path.clear();

	for (std::vector<std::string>::const_iterator it=path.begin();
			it!=path.end(); it++) {
		std::string tmp = *it;
		m_path.push_back(tmp);
	}
}

const std::string &TypePath::leaf() const {
	return (m_path.size()>0)?m_path.at(m_path.size()-1):m_null;
}

TypePath::~TypePath() {
	// TODO Auto-generated destructor stub
}

std::string TypePath::toString() const {
	std::string ret;

	if (isNull()) {
		ret.append("(Empty)");
	} else {
		for (std::vector<std::string>::const_iterator it=m_path.begin();
				it!=m_path.end(); it++) {
			if (ret.size() > 0) {
				ret.append("::");
			}
			ret.append(*it);
		}
	}

	return ret;
}

} /* namespace psi */
