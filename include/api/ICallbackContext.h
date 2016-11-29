/*
 * ICallbackContext.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *  Created on: Aug 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_ICALLBACKCONTEXT_H
#define INCLUDED_ICALLBACKCONTEXT_H
#include <stdint.h>
#include <string>

namespace psi_api {

struct psshandle_s;
typedef psshandle_s *psshandle_t;

class IField;
class ICallbackContext {
public:

	virtual ~ICallbackContext() { }

	virtual int64_t getIntField(
			psshandle_t 	hndl,
			IField 			*field) = 0;

	virtual void setIntField(
			psshandle_t 	hndl,
			IField 			*field,
			int64_t 		v) = 0;

	virtual uint64_t getBitField(
			psshandle_t 	hndl,
			IField 			*field) = 0;

	virtual void setBitField(
			psshandle_t 	hndl,
			IField 			*field,
			uint64_t 		v) = 0;

	virtual bool getBoolField(
			psshandle_t		hndl,
			IField			*field) = 0;

	virtual void setBoolField(
			psshandle_t		hndl,
			IField			*field,
			bool			v) = 0;

	virtual void *getChandleField(
			psshandle_t 	hndl,
			IField 			*field) = 0;

	virtual void setChandleField(
			psshandle_t 	hndl,
			IField 			*field,
			void 			*v) = 0;

	virtual std::string getStringField(
			psshandle_t 	hndl,
			IField 			*field) = 0;

	virtual void setStringField(
			psshandle_t 		hndl,
			IField 				*field,
			const std::string 	&v) = 0;

	/**
	 * Returns the psshandle_t handle for a field of type struct or action
	 */
	virtual psshandle_t getHandleField(
			psshandle_t 		hndl,
			IField 				*field) = 0;

};

}


#endif /* INCLUDED_ICALLBACKCONTEXT_H */
