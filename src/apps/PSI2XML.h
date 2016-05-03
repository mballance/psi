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
#include "IModel.h"

namespace psi {
namespace apps {

class PSI2XML {
public:
	PSI2XML();

	virtual ~PSI2XML();

	virtual const std::string &traverse(IModel *model);

private:
	std::string					m_content;

};

}
}

#endif /* SRC_APPS_PSI2XML_H_ */
