/*
 * test_main.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */
#include <vector>
#include <stdio.h>
#include "Elaborator.h"
#include "TypeRegistry.h"

using namespace psi;

int main(int argc, char **argv) {
	Elaborator elab;

	elab.elaborate(TypeRegistry::global(), nullptr);

//	std::vector<Type *>::const_iterator it;
//	Type *global = TypeRegistry::global();
//
//
//	for (it=global->getChildren().begin();
//			it != global->getChildren().end(); it++) {
//		Type *t = (*it);
//		fprintf(stdout, "Type: %s %s\n",
//				Type::toString(t->getObjectType()),
//				t->getName().c_str());
//	}

	return 0;
}



