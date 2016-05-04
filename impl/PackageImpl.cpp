/*
 * PackageImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "PackageImpl.h"
#include "api/IAction.h"
#include "api/IStruct.h"

namespace psi {

PackageImpl::PackageImpl(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

PackageImpl::~PackageImpl() {
	// TODO Auto-generated destructor stub
}

const std::vector<IAction *> PackageImpl::getActions() {
	return m_actions;
}

IAction *PackageImpl::findAction(const std::string &name) {
	std::vector<IAction *>::iterator it;

	for (it=m_actions.begin(); it!=m_actions.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}

	return 0;
}

void PackageImpl::addAction(IAction *action) {
	m_actions.push_back(action);
}

const std::vector<IStruct *> PackageImpl::getStructs() {
	return m_structs;
}

IStruct *PackageImpl::findStruct(const std::string &name) {
	std::vector<IStruct *>::iterator it;

	for (it=m_structs.begin(); it!=m_structs.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}

	return 0;
}

} /* namespace psi */
