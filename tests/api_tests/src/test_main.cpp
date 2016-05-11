/*
 * test_main.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */
#include <vector>
#include <stdio.h>
#include "psi_tests.h"
#include "ModelImpl.h"
#include "PSI2XML.h"

using namespace psi::apps;

void build_model(IModel *) __attribute__((weak));

/**
 * Default version of the build_model function that uses
 * definitions made by the class library
 */
void build_model(IModel *model) {
	Elaborator elab;

	Type *global = TypeRegistry::global();
	elab.elaborate(TypeRegistry::global(), model);
}

int main(int argc, char **argv) {
	ModelImpl  model;
	PSI2XML    psi2xml;

//	std::vector<IType *>::const_iterator it;

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

	build_model(&model);

	const std::string xml = psi2xml.traverse(&model);

	fprintf(stdout, "Result:\n%s\n", xml.c_str());

	return 0;
}



