/*
 * PSI2StringProcessor.h
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSI2STRINGPROCESSOR_H_
#define SRC_APPS_PSI2STRINGPROCESSOR_H_
#include <stdint.h>
#include <string>

#include "PSIVisitor.h"

namespace psi {
namespace apps {

class PSI2StringProcessor: public PSIVisitor {
public:
	PSI2StringProcessor(uint32_t ind_incr=4);

	virtual ~PSI2StringProcessor();

	virtual const std::string &process(IModel *model);

protected:

	static std::string get_field_qualifiers(IField *f);

	void print(const std::string &str);

	void println(const std::string &str);

	void inc_indent();

	void dec_indent();

	void set_ind_incr(int ind_incr) { m_ind_incr = ind_incr; }

	const std::string &get_indent() const { return m_ind; }

protected:
	std::string					m_ind;
	uint32_t					m_ind_incr;
	std::string					m_content;
};

} /* namespace apps */
} /* namespace psi */

#endif /* SRC_APPS_PSI2STRINGPROCESSOR_H_ */
