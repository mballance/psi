/*
 * action_traversal_activity_stmt.h
 *
 *  Created on: Mar 24, 2017
 *      Author: ballance
 */

#ifndef INCLUDE_PRV_ACTION_TRAVERSAL_ACTIVITY_STMT_H_
#define INCLUDE_PRV_ACTION_TRAVERSAL_ACTIVITY_STMT_H_
#include "prv/activity_stmt.h"

namespace pss {
class action;
namespace prv {

class action_traversal_activity_stmt : public activity_stmt {
public:

	action_traversal_activity_stmt(const pss::action &a);

};

}
}



#endif /* INCLUDE_PRV_ACTION_TRAVERSAL_ACTIVITY_STMT_H_ */
