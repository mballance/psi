/*
 * scope_impl.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ballance
 */

#ifndef CONTRIB_VENDOR_SCOPE_IMPL_H_
#define CONTRIB_VENDOR_SCOPE_IMPL_H_
#include <string>

namespace pss {
namespace vendor {

class base_item;
class scope_impl {
public:
	scope_impl(
			const std::type_info	*type,
			base_item				*ctxt,
			bool					is_field,
			bool					is_type,
			const std::string		&name,
			base_item				*type_id);

	virtual ~scope_impl();

	base_item *ctxt() const { return m_ctxt; }

	void set_ctxt(base_item *ctxt) { m_ctxt = ctxt; }

	const std::type_info *get_typeinfo() const { return m_type; }

	const char *name() const;

	const char *scope_name() const { return m_name.c_str(); }

	void set_scope_name(const std::string &name);

	bool is_field() const { return m_is_field; }

	bool is_type() const { return m_is_type; }

	base_item *type_id() const { return m_type_id; }

private:

	void enter();

	void leave();

private:
	bool					m_is_field;
	bool					m_is_type;
	base_item				*m_ctxt;
	const std::type_info	*m_type;
	std::string				m_name;
	base_item				*m_type_id;
};

} /* namespace vendor */
} /* namespace pss */

#endif /* CONTRIB_VENDOR_SCOPE_IMPL_H_ */
