/*
 * PsiElaborator.h
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_ELABORATOR_ELABORATOR_H_
#define SRC_ELABORATOR_ELABORATOR_H_
#include "Type.h"
#include "Package.h"
#include "IModel.h"
#include "IPackage.h"
#include <vector>

namespace psi {

class Elaborator {
public:

	Elaborator();

	virtual ~Elaborator();

	void elaborate(Type *root, IModel *model);

protected:

	void elaborate_struct(IPackage *pkg, Package *pkg_cl);

private:


};

} /* namespace psi */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
