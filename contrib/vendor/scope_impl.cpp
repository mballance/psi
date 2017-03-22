/*
 * scope_impl.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ballance
 */

#include "scope_impl.h"
#include "model_impl.h"
#include "scope.h"

namespace pss {


scope::scope(const char *name) : scope_impl(0, 0, (name!=0), false, (name)?name:"", 0) {

}

//scope::scope(bool is_type) : scope_impl(0, 0,
//			false, // is_field
//			true, // is_type,
//			"",
//			0) {
//}

scope::~scope() {
}

namespace vendor {

scope_impl::scope_impl(
		const std::type_info	*type,
		base_item				*ctxt,
		bool					is_field,
		bool					is_type,
		const std::string		&name,
		base_item				*type_id) :
	m_type(type), m_ctxt(ctxt),
	m_is_field(is_field), m_is_type(is_type),
	m_name(name), m_type_id(type_id) {

	enter();
}


scope_impl::~scope_impl() {
	leave();
}

//base_item *scope_impl::parent() const {
//	return model_impl::global()->getParentScope();
//}

const char *scope_impl::name() const {
	return m_type->name();
}

void scope_impl::set_scope_name(const std::string &name) {
	m_name = name;
}

//void scope::init(const std::type_info *type, base_item *ctxt, base_item *type_id) {
//	// TODO: type_id
//	m_impl = new scope_impl(this, type, ctxt, false, false, "", type_id);
//}

void scope_impl::enter() {
	model_impl::global()->push_scope(this);
}

void scope_impl::leave() {
	model_impl::global()->pop_scope(this);
}


} /* namespace vendor */
} /* namespace pss */
