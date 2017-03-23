/*
 * NamedBaseItem.h
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_NAMED_BASE_ITEM_H
#define INCLUDED_NAMED_BASE_ITEM_H

#include <string>
#include <stdio.h>
#include "base_item.h"

namespace pss {
namespace vendor {

class named_base_item : public base_item {
public:
	named_base_item(
			base_item::ObjectType 		t,
			base_item 					*p,
			const std::string 			&name="");

	virtual ~named_base_item();

	virtual const std::string &getName() const { return m_name; }

	void setName(const std::string &name) {
		m_name = name;
	}

	static std::string getName(base_item *it);

private:
	std::string					m_name;
};

} /* namespace vendor */
} /* namespace pss */

#endif /* INCLUDED_NAMED_BASE_ITEM_H */
