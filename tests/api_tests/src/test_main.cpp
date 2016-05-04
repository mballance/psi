/*
 * test_main.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */
#include <vector>
#include <stdio.h>
#include "psi.h"
#include "ModelImpl.h"
#include "PSI2XML.h"

using namespace psi;
using namespace psi::apps;

int main(int argc, char **argv) {
	Elaborator elab;
	ModelImpl  model;
	PSI2XML    psi2xml;

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

	const std::string xml = psi2xml.traverse(&model);

	fprintf(stdout, "Result:\n%s\n", xml.c_str());

	return 0;
}



