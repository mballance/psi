/*
 * IObjectContext.h
 *
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IOBJECTCONTEXT_H_
#define SRC_PSI_API_IOBJECTCONTEXT_H_
#include <stdint.h>
#include "api/IBaseItem.h"
#include "api/IField.h"

namespace psi_api {

// Opaque handle to object values
struct psshandle_t;

/**
 * Context API used to access values
 */
class IObjectContext {
public:

	virtual ~IObjectContext() { }

	/**
	 * Returns a handle to the type-specification object corresponding
	 * to the specified handle
	 */
	virtual IBaseItem *getTypeDeclaration(psshandle_t *hndl) = 0;

	/**
	 * Sets the value of the specified primitive field
	 *
	 * hndl - Handle to action/struct object
	 * field - Handle to a type field within that object
	 * v - value to set
	 */
	virtual void setIntField(psshandle_t *hndl, IField *field, int64_t v) = 0;

	virtual int64_t getIntField(psshandle_t *hndl, IField *field) = 0;

	virtual void setBitField(psshandle_t *hndl, IField *field, uint64_t v) = 0;

	virtual uint64_t getBitField(psshandle_t *hndl, IField *field) = 0;

	/**
	 * Returns an object handle to an action/struct type field
	 */
	virtual psshandle_t getObjectField(psshandle_t *hndl, IField *field) = 0;

};

}



#endif /* SRC_PSI_API_IOBJECTCONTEXT_H_ */
