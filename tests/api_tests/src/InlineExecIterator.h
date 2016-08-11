/*
 * InlineExecIterator.h
 *
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_INLINE_EXEC_ITERATOR_H
#define INCLUDED_INLINE_EXEC_ITERATOR_H
#include <string>
#include "api/IModel.h"

using namespace psi_api;

class InlineExecIterator {
public:
	InlineExecIterator(
			IModel				*model,
			const std::string	&comp_name,
			const std::string	&action_name,
			const std::string	&initial
			);

	virtual ~InlineExecIterator();

	bool traverse();

private:

	enum cb_t {
		PreSolve,
		PostSolve,
		Body
	};

	void traverse(IScopeItem *scope, psshandle_t hndl, cb_t cb);

private:
	IModel						*m_model;
	psshandle_t					m_hndl;
	std::string					m_comp_name;
	std::string					m_action_name;
	std::string					m_initial;

};

#endif /* INCLUDED_INLINE_EXEC_ITERATOR_H */

