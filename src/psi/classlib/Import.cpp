/*
 * Import.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "classlib/Import.h"

#include "classlib/ParamList.h"


namespace psi {

Import::Import(const std::string &name, Type *p, const ParamList &plist) :
	Type(Type::TypeImport, name, p){

}

Import::~Import() {
	// TODO Auto-generated destructor stub
}

ImportCall Import::operator()(const ParamList &plist) {
	return ImportCall(*this, plist);
}

ImportCall Import::operator()() {
	return ImportCall(*this, ParamList());
}

} /* namespace psi */
