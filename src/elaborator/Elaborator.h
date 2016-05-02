/*
 * PsiElaborator.h
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_ELABORATOR_ELABORATOR_H_
#define SRC_ELABORATOR_ELABORATOR_H_
#include "Type.h"
#include "IModel.h"

namespace psi {

class Elaborator {
public:

	Elaborator();

	virtual ~Elaborator();

	void elaborate(Type *root, IModel *model);
};

} /* namespace psi */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
