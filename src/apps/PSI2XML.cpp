/*
 * PSI2XML.cpp
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "PSI2XML.h"
#include <stdio.h>

namespace psi {
namespace apps {

PSI2XML::PSI2XML() : m_ind_incr(4) {
	// TODO Auto-generated constructor stub

}

PSI2XML::~PSI2XML() {
	// TODO Auto-generated destructor stub
}

const std::string &PSI2XML::traverse(IModel *model) {
	m_content.clear();

	IPackage *pkg = model->getGlobalPackage();
	process_pkg(pkg);

	std::vector<IBaseItem *>::const_iterator it=model->getItems().begin();

	for (; it!=model->getItems().end(); it++) {
		IBaseItem *i = *it;

		if (i->getType() == IBaseItem::TypePackage) {
			IPackage *pkg = static_cast<IPackage *>(i);
			process_pkg(pkg);
		} else if (i->getType() == IBaseItem::TypeComponent) {
		} else {
			// Really shouldn't be anything else in the global scope
		}
	}


	return m_content;
}

void PSI2XML::process_pkg(IPackage *pkg) {
	if (pkg->getName() == "") {
		println("<package>");
	} else {
		println("<package name=\"" + pkg->getName() + "\">");
	}

	inc_indent();

	std::vector<IBaseItem *>::const_iterator it=pkg->getItems().begin();

	for (; it!=pkg->getItems().end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
			case IBaseItem::TypeAction:
				break;

			case IBaseItem::TypeStruct:
				process_struct(static_cast<IStruct *>(i));
				break;
		}
	}

	dec_indent();

	println("</package>");
}

void PSI2XML::process_struct(IStruct *str) {
	println("<struct name=\"" + str->getName() + "\">");
	// TODO: handle super-type

	println("</struct>");
}

void PSI2XML::println(const std::string &str) {
	m_content.append(m_ind);
	m_content.append(str);
	m_content.append("\n");
}

void PSI2XML::inc_indent() {
	for (int i=0; i<m_ind_incr; i++) {
		m_ind.append(" ");
	}
}

void PSI2XML::dec_indent() {
	if (m_ind.size() > m_ind_incr) {
		m_ind.resize(m_ind.size()-m_ind_incr);
	} else {
		m_ind.clear();
	}
}


}
}
