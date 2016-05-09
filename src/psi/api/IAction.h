/*
 * IAction.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_PROGRAMMATIC_IACTION_H_
#define SRC_PROGRAMMATIC_IACTION_H_
#include <string>
#include <vector>

#include "api/IBaseItem.h"
#include "api/IGraphStmt.h"

namespace psi_api {
	/**
	 * Class: IAction
	 * Specifies the API to an Action declaration
	 */
	class IAction : public IBaseItem {

		public:

			virtual ~IAction() { };

			/**
			 * Method: getName
			 * Returns the name of the action
			 */
			virtual const std::string &getName() const = 0;

			/**
			 * Method: getItems
			 * Returns a list of the sub-elements of the action.
			 */
			virtual const std::vector<IBaseItem *> &getItems() const = 0;

			/**
			 * Method: add
			 * Adds a new sub-element to the action declaration
			 */
			virtual void add(IBaseItem *it) = 0;

			/**
			 * Method: getGraph
			 * Returns the graph body, or null if there is none
			 */
			virtual IGraphStmt *getGraph() = 0;

			/**
			 * Method: setGraph
			 * Sets the graph body
			 */
			virtual void setGraph(IGraphStmt *graph) = 0;

	};
}




#endif /* SRC_PROGRAMMATIC_IACTION_H_ */
