/*
 * action_attr.h
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
 *  Created on: Dec 22, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_ACTION_ATTR_H
#define INCLUDED_ACTION_ATTR_H

#include <string>

#include "classlib/FieldBase.h"
#include "classlib/pss_int.h"
#include "classlib/pss_bit.h"

namespace pss {

template <class T> class action_attr : public FieldBase<T> {
	public:

		action_attr(const Scope &name) : FieldBase<T>(FieldItem::AttrAction, name) { }

//		action_attr(BaseItem *p, const std::string &name) :
//			FieldBase<T>(FieldItem::AttrAction, p, name) { }
//
//		action_attr(BaseItem *p, const std::string &name, const Expr &array_dim) :
//			FieldBase<T>(FieldItem::AttrAction, p, name, array_dim) { }

		virtual ~action_attr() { }

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

template <> class action_attr<pss_int> : public FieldItem {
public:

	action_attr(const Scope &name) :
		FieldItem(this, FieldItem::AttrAction, pss_int(), 0) { }

	action_attr(const Scope &name, const pss_int &t_decl) :
		FieldItem(this, FieldItem::AttrAction, t_decl, 0) { }

	void set(int64_t v) { set_int(v); }

	int64_t get() { return get_int(); }
};

template <> class action_attr<pss_bit> : public FieldItem {
public:
	action_attr(const Scope &name) :
		FieldItem(this, FieldItem::AttrAction, pss_bit(), 0) { }

	action_attr(const Scope &name, const pss_bit &t_decl) :
		FieldItem(this, FieldItem::AttrAction, t_decl, 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }

};

template <> class action_attr<unsigned long long> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_bit(64), 0) { }

	void set(uint64_t v) { set_bit(v); }

	uint64_t get() { return get_bit(); }
};

template <> class action_attr<long long> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_int(64), 0) { }

	void set(int64_t v) { set_int(v); }

	int64_t get() { return get_int(); }

};

template <> class action_attr<unsigned int> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_bit(32), 0) { }

	void set(uint32_t v) { set_bit(v); }

	uint32_t get() { return get_bit(); }
};

template <> class action_attr<int> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_int(32), 0) { }

	void set(int32_t v) { set_int(v); }

	int32_t get() { return get_int(); }

};

template <> class action_attr<unsigned short> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_bit(16), 0) { }

	void set(uint16_t v) { set_bit(v); }

	uint16_t get() { return get_bit(); }
};

template <> class action_attr<short> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_int(16), 0) { }

	void set(int16_t v) { set_int(v); }

	int16_t get() { return get_int(); }

};

template <> class action_attr<unsigned char> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_bit(8), 0) { }

	void set(uint8_t v) { set_bit(v); }

	uint8_t get() { return get_bit(); }
};

template <> class action_attr<char> : public FieldItem {
public:

	action_attr(const std::string &name) :
		FieldItem(this, FieldItem::AttrAction, pss_int(8), 0) { }

	void set(int8_t v) { set_int(v); }

	int8_t get() { return get_int(); }
};

template <> class action_attr<bool> : public FieldItem {
public:
	action_attr(const Scope &name) :
		FieldItem(name, FieldItem::AttrAction, pss_bool(), 0) { }

	void set(bool v) { set_bit(v); }

	bool get() { return get_bit(); }
};

}



#endif /* INCLUDED_ACTION_ATTR_H */
