/*
 * NamedBaseItem.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_NAMED_BASE_ITEM_IMP_H
#define INCLUDED_NAMED_BASE_ITEM_IMP_H

#include <string>
#include <stdio.h>
#include "BaseItemImp.h"

namespace pss {

class NamedBaseItemImp : public BaseItemImp {
public:
	NamedBaseItemImp(
			BaseItem 					*master,
			BaseItemImp::ObjectType 	t,
			BaseItem 					*p,
			const std::string 			&name="");

	virtual ~NamedBaseItemImp();

	virtual const std::string &getName() const { return m_name; }

	void setName(const std::string &name) {
		m_name = name;
	}

	static NamedBaseItemImp *to(BaseItemImp *it);

	static std::string getName(BaseItemImp *it);

private:
	std::string					m_name;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_ */
