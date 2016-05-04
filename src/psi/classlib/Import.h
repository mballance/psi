/*
 * Import.h
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_IMPORT_H_
#define SRC_STATIC_IMPORT_H_
#include <string>

#include "classlib/ImportCall.h"
#include "classlib/Type.h"

namespace psi {

class ExprList;
class Import : public Type {

	public:

		Import(const std::string &name, Type *p, const ExprList &plist);

		virtual ~Import();

		ImportCall operator()(const ExprList &plist);

		ImportCall operator()();
};


} /* namespace psi */

#endif /* SRC_STATIC_IMPORT_H_ */
