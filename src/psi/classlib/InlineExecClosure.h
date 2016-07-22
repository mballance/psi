/*
 * InlineExecClosure.h
 *
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef IMPL_INLINEEXECIMPL_H_
#define IMPL_INLINEEXECIMPL_H_
#include "api/IInlineExec.h"

using namespace psi_api;

namespace psi {

template <class T> class InlineExecClosure : public psi_api::IInlineExec {
public:

	InlineExecClosure(
			T *t,
			void (T::*init)(psi_api::IObject *obj),
			void (T::*exec)()) : m_target(t), m_init(init), m_exec(exec) { }

	virtual ~InlineExecClosure() { }

	virtual void exec(psi_api::IObject *obj) {
		// Pass the context object on
		((*m_target).*m_init)(obj);
		// Call the actual exec method
		((*m_target).*m_exec)();
	}

private:
	T				*m_target;
	void (T::*m_init)(psi_api::IObject *);
	void (T::*m_exec)();
};

}



#endif /* IMPL_INLINEEXECIMPL_H_ */
