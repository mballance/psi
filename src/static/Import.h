/*
 * Import.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_IMPORT_H_
#define SRC_STATIC_IMPORT_H_
#include <string>

#include "Type.h"
#include "ImportCall.h"

namespace psi {

class ParamList;
class IConstructorContext;
class Import : public Type {

	public:

		Import(const std::string &name, Type *p, const ParamList &plist);

		virtual ~Import();

		ImportCall operator()(const ParamList &plist);

		ImportCall operator()();
};


} /* namespace psi */

#endif /* SRC_STATIC_IMPORT_H_ */
