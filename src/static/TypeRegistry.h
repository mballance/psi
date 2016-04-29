/*
 * TypeRegistry.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_TYPEREGISTRY_H_
#define SRC_TYPEREGISTRY_H_

#include <string>

#include "DeclarationScope.h"
#include "IConstructorContext.h"

namespace psi {

class TypeFactoryBase;
class Package;
class TypeRegistry : public virtual IConstructorContext, public DeclarationScope {
	friend class Package;

	public:
		TypeRegistry();

		virtual ~TypeRegistry();

//		void register_type(TypeFactoryBase *f, ObjectType t);

		virtual IConstructorContext::ConstructorContextType getContextType() {
			return IConstructorContext::Global;
		}

		virtual IObjectType::ObjectType getObjectType();

		virtual IConstructorContext *getParent() {
			return nullptr;
		}

		static TypeRegistry *global();

	private:

		static TypeRegistry			*m_global;

};

class TypeFactoryBase {
	protected:

		std::string							m_name;

	public:

		TypeFactoryBase(const std::string &name);

		virtual ~TypeFactoryBase();

		virtual void *create(IConstructorContext *p) = 0;

		const std::string &get_name() const { return m_name; }
};

//template <class T> class TypeFactory : public TypeFactoryBase {
//	public:
//
//		TypeFactory(const std::string &name, TypeRegistry *rgy) : TypeFactoryBase(name) {
//			rgy->register_type(this, T::m_object_type); // TODO
//		}
//
//		virtual void *create(IConstructorContext *p) {
//			return new T(p, m_name);
//		}
//
//};



} /* namespace psi */


#endif /* SRC_TYPEREGISTRY_H_ */
