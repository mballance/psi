/*
 * InlineExecClosure.h
 *
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef IMPL_INLINEEXECIMPL_H_
#define IMPL_INLINEEXECIMPL_H_
#include "api/IBaseItem.h"
#include "api/IInlineExec.h"

using namespace psi_api;

namespace psi {

template <class T> class InlineExecClosure : public psi_api::IInlineExec {
public:

	InlineExecClosure(
			T 				*t,
			void (T::*pre)(psi_api::IObjectContext *ctxt, psshandle_t *hndl),
			void (T::*exec)(),
			void (T::*post)()) : m_target(t), m_pre(pre), m_exec(exec), m_post(post) { }

	virtual ~InlineExecClosure() { }

	virtual void exec(psi_api::IObjectContext *ctxt, psshandle_t *hndl) {
		// Pass the context object on
		((*m_target).*m_pre)(ctxt, hndl);
		// Call the actual exec method
		((*m_target).*m_exec)();
		// Call 'post' to cleanup
		((*m_target).*m_post)();
	}

private:
	T				*m_target;
	void (T::*m_pre)(psi_api::IObjectContext *, psshandle_t *);
	void (T::*m_exec)();
	void (T::*m_post)();
};

}



#endif /* IMPL_INLINEEXECIMPL_H_ */
