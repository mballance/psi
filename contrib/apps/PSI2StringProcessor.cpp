/*
 * PSI2StringProcessor.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#include "PSI2StringProcessor.h"

namespace psi {
namespace apps {

PSI2StringProcessor::PSI2StringProcessor(uint32_t ind_incr) {
	set_ind_incr(ind_incr);
}

PSI2StringProcessor::~PSI2StringProcessor() {
	// TODO Auto-generated destructor stub
}

const std::string &PSI2StringProcessor::process(IModel *model) {
	visit_model(model);

	return m_content;
}

std::string PSI2StringProcessor::get_field_qualifiers(IField *f) {
	std::string ret;

	switch (f->getAttr()) {
	case IField::FieldAttr_Rand: ret = "rand"; break;
	case IField::FieldAttr_Input: ret = "input"; break;
	case IField::FieldAttr_Output: ret = "output"; break;
	case IField::FieldAttr_Lock: ret = "lock"; break;
	case IField::FieldAttr_Share: ret = "share"; break;
	case IField::FieldAttr_Pool: ret = "pool"; break;
	}

	return ret;
}

void PSI2StringProcessor::print(const std::string &str) {
	m_content.append(str);
}

void PSI2StringProcessor::println(const std::string &str) {
	m_content.append(m_ind);
	m_content.append(str);
	m_content.append("\n");
}

void PSI2StringProcessor::inc_indent() {
	for (int i=0; i<m_ind_incr; i++) {
		m_ind.append(" ");
	}
}

void PSI2StringProcessor::dec_indent() {
	if (m_ind.size() > m_ind_incr) {
		m_ind.resize(m_ind.size()-m_ind_incr);
	} else {
		m_ind.clear();
	}
}

} /* namespace apps */
} /* namespace psi */
