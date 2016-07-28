/*
 * Bind.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "BindImp.h"

namespace psi {

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2) :
		BaseItem(new BindImp(this, p->impl())) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl());
	imp->add(i2.impl());
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3) :
		BaseItem(new BindImp(this, p->impl())) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl());
	imp->add(i2.impl());
	imp->add(i3.impl());
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4) : BaseItem(new BindImp(this, p->impl())) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl());
	imp->add(i2.impl());
	imp->add(i3.impl());
	imp->add(i4.impl());
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4, BaseItem &i5) : BaseItem(new BindImp(this, p->impl())) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl());
	imp->add(i2.impl());
	imp->add(i3.impl());
	imp->add(i4.impl());
	imp->add(i5.impl());
}


Bind::Bind(BaseItem *p, const std::vector<BaseItem *> &items) :
		BaseItem(new BindImp(this, p->impl())) {
	BindImp *imp = static_cast<BindImp *>(impl());

	for (std::vector<BaseItem *>::const_iterator it=items.begin();
			it != items.end(); it++) {
		BaseItem *it_p = *it;
		imp->add(it_p->impl());
	}
}

Bind::~Bind() {
}

} /* namespace psi */
