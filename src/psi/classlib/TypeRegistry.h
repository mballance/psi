/*
 * TypeRegistry.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_TYPEREGISTRY_H_
#define SRC_TYPEREGISTRY_H_

#include <string>

#include "classlib/Type.h"

namespace psi {

class Package;
class TypeRegistry : public Type {
	friend class Package;

	public:
		TypeRegistry();

		virtual ~TypeRegistry();

		static TypeRegistry *global();

	private:

		static TypeRegistry			*m_global;

};


} /* namespace psi */


#endif /* SRC_TYPEREGISTRY_H_ */
