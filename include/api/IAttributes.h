/*
 * IAttributes.h
 *
 *  Created on: Aug 15, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IATTRIBUTES_H
#define INCLUDED_IATTRIBUTES_H
#include <string>
#include <vector>

namespace psi_api {

class IAttributes {
public:
	virtual ~IAttributes() { }

	virtual const std::string &getAttribute(const std::string &key) = 0;

	virtual void getAttributes(std::vector<std::string> &keys) = 0;

	virtual bool hasAttribute(const std::string &key) = 0;

	virtual void setAttribute(const std::string &key, const std::string &val) = 0;

	virtual void clearAttribute(const std::string &key) = 0;

};

}


#endif /* INCLUDED_IATTRIBUTES_H */
