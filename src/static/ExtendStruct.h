/*
 * ExtendStruct.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDSTRUCT_H_
#define SRC_STATIC_EXTENDSTRUCT_H_

namespace psi {

template <class T> class ExtendStruct : public T {

	public:
		ExtendStruct(Type *p, T &t_ref) : T("<Extend>", p) {
			Type *t = static_cast<Type *>(this);
			t->setTypeData(&t_ref);
			t->setObjectType(Type::TypeExtendStruct);
		}

		virtual ~ExtendStruct() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDSTRUCT_H_ */
