/*
 * MethodParamListImp.cpp
 *
 *  Created on: Aug 26, 2016
 *      Author: ballance
 */

#include "MethodParamListImp.h"
#include "FieldItemImp.h"

namespace pss {

MethodParamList::MethodParamList() : m_imp(new MethodParamListImp(this)) {
	m_imp->inc_refcnt();
}

MethodParamList::MethodParamList(const MethodParamList &rhs) {
	m_imp = rhs.m_imp;
	m_imp->inc_refcnt();
}

MethodParamList::MethodParamList(const FieldItem &rhs) :
		m_imp(new MethodParamListImp(this)) {
	m_imp->add(rhs);
	m_imp->inc_refcnt();
}

MethodParamListImp::MethodParamListImp(MethodParamList *master) : m_refcnt(0) {
	// TODO Auto-generated constructor stub

}

MethodParamList::~MethodParamList() {
	m_imp->dec_refcnt();
}

MethodParamListImp::~MethodParamListImp() {
	// TODO Auto-generated destructor stub
}

MethodParamList MethodParamList::operator,(const FieldItem &rhs) {
	m_imp->add(rhs);
	return *(this);
}

MethodParamListImp *MethodParamList::imp() const {
	return m_imp;
}

void MethodParamListImp::add(const FieldItem &rhs) {
	m_parameters.push_back(rhs);
}

void MethodParamListImp::inc_refcnt() {
	m_refcnt++;
}

void MethodParamListImp::dec_refcnt() {
	if (m_refcnt == 0) {
		fprintf(stdout, "Error: MethodParamListImp dec_refcnt error\n");
	}

	m_refcnt--;

	if (m_refcnt == 0) {
		delete this;
	}
}

} /* namespace pss */
