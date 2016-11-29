/*
 * Bind.cpp
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "BindImp.h"

namespace pss {

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2) :
		BaseItem(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl(), false);
	imp->add(i2.impl(), false);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3) :
		BaseItem(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl(), false);
	imp->add(i2.impl(), false);
	imp->add(i3.impl(), false);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4) : BaseItem(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl(), false);
	imp->add(i2.impl(), false);
	imp->add(i3.impl(), false);
	imp->add(i4.impl(), false);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4, BaseItem &i5) : BaseItem(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	imp->add(i1.impl(), false);
	imp->add(i2.impl(), false);
	imp->add(i3.impl(), false);
	imp->add(i4.impl(), false);
	imp->add(i5.impl(), false);
}


Bind::Bind(BaseItem *p, const std::vector<BaseItem *> &items) :
		BaseItem(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	for (std::vector<BaseItem *>::const_iterator it=items.begin();
			it != items.end(); it++) {
		BaseItem *it_p = *it;
		imp->add(it_p->impl(), false);
	}
}

BindImp::BindImp(Bind *master, BaseItem *p) :
	BaseItemImp(master, BaseItemImp::TypeBind, p) {

}

Bind::~Bind() {

}

BindImp::~BindImp() {

}

} /* namespace pss */
