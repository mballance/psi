/*
 * TypePath.h
 *
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_TYPEPATH_H_
#define SRC_PSI_CLASSLIB_TYPEPATH_H_
#include <string>
#include <vector>

namespace psi {

class TypePath {
public:

	TypePath();

	TypePath(const std::string &path);

	TypePath(const std::vector<std::string> &path);

	virtual ~TypePath();

	bool isNull() const { return m_path.size() == 0; }

	const std::vector<std::string> &get() const { return m_path; }

	void set(const std::vector<std::string> &path);

	const std::string &leaf() const;

	void prepend(const std::string &elem) { m_path.insert(m_path.begin(), elem); }

	void append(const std::string &elem) { m_path.push_back(elem); }

	std::string toString() const;

private:
	std::vector<std::string>		m_path;
	std::string						m_null;

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_TYPEPATH_H_ */
