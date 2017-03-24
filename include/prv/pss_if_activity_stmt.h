/*
 * pss_if_activity_stmt.h
 *
 *  Created on: Mar 24, 2017
 *      Author: ballance
 */

#ifndef INCLUDE_PRV_PSS_IF_ACTIVITY_STMT_H_
#define INCLUDE_PRV_PSS_IF_ACTIVITY_STMT_H_
#include "prv/activity_stmt.h"

namespace pss {
class pss_if;
namespace prv {

class pss_if_activity_stmt : prv::activity_stmt {
public:

	pss_if_activity_stmt(const pss_if &if_stmt);

};

}
}



#endif /* INCLUDE_PRV_PSS_IF_ACTIVITY_STMT_H_ */
