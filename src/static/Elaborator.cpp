/*
 * PsiElaborator.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "Elaborator.h"
#include <stdio.h>

namespace psi {

using namespace std;

Elaborator::Elaborator() {
	// TODO Auto-generated constructor stub

}

Elaborator::~Elaborator() {
	// TODO Auto-generated destructor stub
}

void Elaborator::elaborate(Type *root, IModel *model) {
	vector<Type *>::const_iterator it;

	// First, go through and declare global data types
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		Type *t = (*it);

		fprintf(stdout, "t=%p\n", t);

		if (t->getObjectType() == Type::TypeStruct) {
			elaborate_struct(model->getGlobalPackage(), static_cast<Package *>(t));
		}
	}
}

void Elaborator::elaborate_struct(IPackage *pkg, Package *pkg_cl) {
	fprintf(stdout, "elaborate_struct: %s\n", pkg_cl->getName().c_str());
}

} /* namespace psi */
