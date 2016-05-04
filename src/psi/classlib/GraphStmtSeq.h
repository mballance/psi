/*
 * GraphStmtSeq.h
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_GRAPHSTMTSEQ_H_
#define SRC_STATIC_GRAPHSTMTSEQ_H_
#include "classlib/Type.h"

namespace psi {
class GraphStmtSeq {

public:

	GraphStmtSeq();

	GraphStmtSeq(const Type &p);

	virtual ~GraphStmtSeq();

	GraphStmtSeq operator,(const Type &lhs);
};

}

#endif /* SRC_STATIC_GRAPHSTMTSEQ_H_ */
