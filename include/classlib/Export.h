/*
 * Export.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXPORT_H_
#define SRC_PSI_CLASSLIB_EXPORT_H_
#include "classlib/ExportItem.h"
#include "classlib/TypeDecl.h"

namespace psi {

template <class T> class Export : public T {
public:
	Export(BaseItem *p) : T(Scope(true)), m_item(p) {
		m_item.setDataType(TypeDecl<T>::id());
	}

	Export(BaseItem *p, const ExprList &exp_params) : T(Scope(true)), m_item(p, exp_params) {
		m_item.setDataType(TypeDecl<T>::id());
	}

private:
	ExportItem				m_item;


};

}


#endif /* SRC_PSI_CLASSLIB_EXPORT_H_ */
