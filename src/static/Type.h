/*
 * Type.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef TYPE_H_
#define TYPE_H_
#include <string>
#include "IConstructorContext.h"
#include "DeclarationScope.h"

namespace psi {

class Action;

class Type : public DeclarationScope, public virtual IConstructorContext {

	public:

		// TODO: remove
		Type(IConstructorContext *p, const std::string &name="");

		Type(const std::string &name, IConstructorContext *p=nullptr);

		virtual ~Type();

		virtual IConstructorContext::ConstructorContextType getContextType() {
			// TODO: Placeholder for now
			return ConstructorContext_TypeElab;
		}

		virtual IConstructorContext *getParent() {
			return m_parent;
		}

		virtual IObjectType::ObjectType getObjectType() {
			// TODO: Placeholder for now
			return IObjectType::Type;
		}

		inline const std::string &getName() const { return m_name; }

		inline bool isRand() const { return m_isRand; }

		inline void setIsRand(bool r) { m_isRand = r; }

		inline bool isInput() const { return m_isInput; }

		inline void setIsInput(bool i) { m_isInput = i; m_isOutput = false; }

		inline bool isOutput() const { return m_isOutput; }

		inline void setIsOutput(bool o) { m_isOutput = o; m_isInput = false; }

		inline Type *getTypeData() const { return m_type_data; }

		inline void setTypeData(Type *t) { m_type_data = t; }

	private:

		bool insideInstance();

	private:
		std::string					m_name;
		IConstructorContext			*m_parent;

		Type						*m_type_data;

		bool						m_isRand;
		bool						m_isInput;
		bool						m_isOutput;

//		virtual void add(psi::Action *action);
//
//		virtual void add(psi::Component *component);
//
//		virtual void add(psi::Package *package);
//
//		virtual void addField(psi::Type *t);

};

} /* namespace psi */

#endif /* TYPE_H_ */
