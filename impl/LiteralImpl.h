/*
 * LiteralImpl.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_LITERALIMPL_H_
#define IMPL_LITERALIMPL_H_
#include <string>
#include "api/ILiteral.h"

namespace psi {

class LiteralImpl : public ILiteral {
public:
	LiteralImpl(int64_t v);

	LiteralImpl(uint64_t v);

	LiteralImpl(bool v);

	LiteralImpl(const std::string &s);

	virtual ~LiteralImpl();

	virtual ExprType getType() const { return IExpr::ExprType_Literal; }

	virtual LiteralType getLiteralType() const { return m_literalType; }

	virtual int64_t getInt() const { return (int64_t)m_intval; }

	virtual uint64_t getBit() const { return m_intval; }

	virtual bool getBool() const { return (m_intval)?true:false; }

	virtual const std::string &getString() const { return m_strval; }


private:
	ILiteral::LiteralType			m_literalType;
	uint64_t						m_intval;
	std::string						m_strval;

};

} /* namespace psi */

#endif /* IMPL_LITERALIMPL_H_ */
