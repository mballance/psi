/*
 * extend_item.h
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

#ifndef INCLUDED_EXTEND_ITEM_IMP_H
#define INCLUDED_EXTEND_ITEM_IMP_H

#include "classlib/extend_item.h"
#include "BaseItemImp.h"

namespace pss {

class ExtendItemImp: public BaseItemImp {
public:
	ExtendItemImp(
			extend_item 				*master,
			base_item 				*p,
			base_item				*type_hndl,
			base_item				*ext_hndl
			);

	virtual ~ExtendItemImp();

	void setDataType(base_item *dt);

	BaseItemImp *getDataType() const { return m_data_type; }

	BaseItemImp *getExtHndl() const { return m_ext_hndl; }

private:

	BaseItemImp				*m_data_type;
	BaseItemImp				*m_ext_hndl;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXTENDITEM_H_ */
