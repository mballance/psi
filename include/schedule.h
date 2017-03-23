/*
 * schedule.h
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
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCHEDULE_H
#define INCLUDED_SCHEDULE_H
#include <vector>
#include "prv/activity_stmt.h"

namespace pss {

class schedule: public expr {
public:
	schedule(const std::vector<prv::activity_stmt> &body);

	template <class... I> schedule(const I&... /* prv::activity_stmt */ items);

	virtual ~schedule();

};

} /* namespace pss */

#endif /* INCLUDED_SCHEDULE_H */
