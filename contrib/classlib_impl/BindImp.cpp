/*
 * bind.cpp
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

bind::bind(base_item *p, const std::vector<attr_item *> &items) :
		base_item(new BindImp(this, p)) {
	BindImp *imp = static_cast<BindImp *>(impl());

	for (std::vector<attr_item *>::const_iterator it=items.begin();
			it != items.end(); it++) {
		attr_item *it_p = *it;
		imp->add(it_p->impl(), false);
	}
}

BindImp::BindImp(bind *master, base_item *p) :
	BaseItemImp(master, BaseItemImp::TypeBind, p) {

}

bind::~bind() {

}

BindImp::~BindImp() {

}

} /* namespace pss */
