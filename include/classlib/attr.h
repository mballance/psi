/*
 * attr.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FIELD_H
#define INCLUDED_FIELD_H

#include <string>

#include "classlib/FieldBase.h"
#include "classlib/pss_int.h"
#include "classlib/pss_bit.h"

namespace pss {

template <class T> class attr : public FieldBase<T> {
	public:

		attr(const Scope &name) : FieldBase<T>(FieldItem::AttrNone, name) { }

//		attr(BaseItem *p, const std::string &name) :
//			FieldBase<T>(FieldItem::AttrNone, p, name) { }
//
//		attr(BaseItem *p, const std::string &name, const Expr &array_dim) :
//			FieldBase<T>(FieldItem::AttrNone, p, name, array_dim) { }

		virtual ~attr() { }

#ifdef UNDEFINED
		ExecStmt operator =(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field = rhs); }

		ExecStmt operator =(const Expr &rhs) { return (FieldBase<T>::m_field = rhs); }

		ExecStmt operator +=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field += rhs); }

		ExecStmt operator +=(const Expr &rhs) { return (FieldBase<T>::m_field += rhs); }

		ExecStmt operator -=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field -= rhs); }

		ExecStmt operator -=(const Expr &rhs) { return (FieldBase<T>::m_field -= rhs); }

		ExecStmt operator <<=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field <<= rhs); }

		ExecStmt operator <<=(const Expr &rhs) { return (FieldBase<T>::m_field <<= rhs); }

		ExecStmt operator >>=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field >>= rhs); }

		ExecStmt operator >>=(const Expr &rhs) { return (FieldBase<T>::m_field >>= rhs); }

		ExecStmt operator |=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field |= rhs); }

		ExecStmt operator |=(const Expr &rhs) { return (FieldBase<T>::m_field |= rhs); }

		ExecStmt operator &=(const ExecImportCallStmt &rhs) { return (FieldBase<T>::m_field &= rhs); }

		ExecStmt operator &=(const Expr &rhs) { return (FieldBase<T>::m_field &= rhs); }
#endif

};

template <> class attr<pss_int> : public FieldItem {
public:

	attr(const Scope &name) :
		FieldItem(this, FieldItem::AttrNone, pss_int(), 0) { }

	attr(const Scope &name, const pss_int &t_decl) :
		FieldItem(this, FieldItem::AttrNone, t_decl, 0) { }

//	operator const FieldItem &() const { return m_field; }

//	operator Expr() const { return Expr(m_field); }

};

#ifdef UNDEFINED
template <> class attr<pss_bit> {
public:

	attr(const std::string &name, const pss_bit &t_decl) : m_type(t_decl),
		m_field(0, name, 0, FieldItem::AttrNone, 0, 0, &m_type) { }

	operator const FieldItem &() const { return m_field; }

	operator Expr() const { return Expr(m_field); }

protected:

private:
	pss_int					m_type;
	FieldItem				m_field;
};

template <> class attr<unsigned int> {
public:

	attr(const std::string &name) : m_type(32),
		m_field(0, name, 0, FieldItem::AttrNone, 0, 0, &m_type) { }

	operator const FieldItem &() const { return m_field; }

	operator Expr() const { return Expr(m_field); }

protected:

private:
	pss_bit					m_type;
	FieldItem				m_field;
};

template <> class attr<int> {
public:

	attr(const std::string &name) : m_type(32),
		m_field(0, name, 0, FieldItem::AttrNone, 0, 0, &m_type) { }

	operator const FieldItem &() const { return m_field; }

	operator Expr() const { return Expr(m_field); }

protected:

private:
	pss_int					m_type;
	FieldItem				m_field;
};
#endif /* UNDEFINED */

}



#endif /* SRC_CLASSLIB_FIELD_H_ */
