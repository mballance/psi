/*
 * PSI2XML.h
 *
 * Traverses a Semantic Model description using the PSI API
 * and writes an XML file as output
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSI2XML_H_
#define SRC_APPS_PSI2XML_H_
#include <string>
#include <stdint.h>

#include "api/IModel.h"

namespace psi {
namespace apps {

class PSI2XML {
public:
	PSI2XML();

	virtual ~PSI2XML();

	virtual const std::string &traverse(IModel *model);


private:

	void process_pkg(IPackage *pkg);

	void process_struct(IStruct *str);

	void println(const std::string &str);

	void inc_indent();
	void dec_indent();

private:
	std::string					m_ind;
	uint32_t					m_ind_incr;
	std::string					m_content;


};

}
}

#endif /* SRC_APPS_PSI2XML_H_ */
