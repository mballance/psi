/*
 * component.h
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_COMPONENT_IMP_H
#define INCLUDED_COMPONENT_IMP_H
#include <string>

#include "NamedBaseItemImp.h"
#include "TypePathImp.h"
#include "classlib/component.h"

namespace pss {

class attr_item;
class ComponentImp : public NamedBaseItemImp {

	public:
		ComponentImp(component *master, ScopeImp *p);

		virtual ~ComponentImp();

		const TypePathImp &getSuperType() const { return m_super_type; }

		attr_item &getField() const { return *m_field; }

		virtual const std::string &getName() const;

	private:
		TypePathImp				m_super_type;
		attr_item				*m_field;

};

} /* namespace pss */

#endif /* COMPONENT_H_ */
