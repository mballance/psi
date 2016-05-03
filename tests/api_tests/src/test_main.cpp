/*
 * test_main.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */
#include <vector>
#include <stdio.h>
#include "psi.h"
#include "Elaborator.h"
#include "TypeRegistry.h"
#include "ModelImpl.h"

using namespace psi;

int main(int argc, char **argv) {
	Elaborator elab;
	ModelImpl  model;

//	std::vector<IType *>::const_iterator it;
	Type *global = TypeRegistry::global();

//	fprintf(stdout, "Vector size: %d\n", global->getChildren().size());
//	for (it=global->getChildren().begin();
//			it != global->getChildren().end(); ++it) {
//		Type *t = (*it);
//		fprintf(stdout, "PTR: %p\n", t);
//		if (t != nullptr) {
//		fprintf(stdout, "Type: %s %s\n",
//				Type::toString(t->getObjectType()),
//				t->getName().c_str());
//		}
//	}

	elab.elaborate(TypeRegistry::global(), &model);

	return 0;
}



