/*
 * activity_stmt.h
 *
 *  Created on: Mar 23, 2017
 *      Author: ballance
 */

#ifndef INCLUDE_PRV_ACTIVITY_STMT_H_
#define INCLUDE_PRV_ACTIVITY_STMT_H_

namespace pss {
class pss_if;
class foreach;
class action;
namespace prv {

class activity_stmt : public vendor::activity_stmt_impl {
public:

	activity_stmt(const foreach &foreach_stmt);

//	activity_stmt(const action &a);

};

} /* namespace prv */
} /* namespace pss */


#endif /* INCLUDE_PRV_ACTIVITY_STMT_H_ */
