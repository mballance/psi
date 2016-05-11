/*
 * NativeExecClosure.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_NATIVEEXECCLOSURE_H_
#define SRC_PSI_CLASSLIB_NATIVEEXECCLOSURE_H_
#include <stdio.h>

namespace psi {

class NativeExecClosureBase {
public:

	NativeExecClosureBase();
	virtual ~NativeExecClosureBase();

	virtual void run() = 0;

};

template <class C> class NativeExecClosure : public NativeExecClosureBase {
public:

	NativeExecClosure(C *this_ptr, void (C::*fp)()) {
		m_this_ptr = this_ptr;
		m_fp = fp;
	}

	virtual void run() {
		fprintf(stdout, "virtual run: %p %p\n", m_this_ptr, m_fp);
		((*m_this_ptr).*m_fp)();
	}

private:
	C				*m_this_ptr;
	void 		(C::*m_fp)();
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_NATIVEEXECCLOSURE_H_ */
