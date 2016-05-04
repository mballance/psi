/*
 * PsiElaborator.h
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_ELABORATOR_ELABORATOR_H_
#define SRC_ELABORATOR_ELABORATOR_H_
#include <vector>

#include "api/IAction.h"
#include "api/IModel.h"
#include "api/IPackage.h"
#include "classlib/Action.h"
#include "classlib/Component.h"
#include "classlib/Package.h"
#include "classlib/Type.h"
#include "classlib/Struct.h"

namespace psi {

class Elaborator {
public:

	Elaborator();

	virtual ~Elaborator();

	void elaborate(Type *root, IModel *model);

protected:

	IAction *elaborate_action(Action *a);

	void elaborate_component(Component *c);

	void elaborate_struct(IPackage *pkg, Struct *str);

	void elaborate_package(IModel *model, Package *pkg_cl);

private:

	void error(const std::string &msg);

private:
	IModel					*m_model;



};

} /* namespace psi */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
