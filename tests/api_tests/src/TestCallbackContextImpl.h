/*
 * TestCallbackContextImpl.h
 *
 *  Created on: Aug 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_TEST_CALLBACK_CONTEXT_IMPL_H
#define INCLUDED_TEST_CALLBACK_CONTEXT_IMPL_H
#include "api/ICallbackContext.h"
#include "api/IField.h"
#include "api/IModel.h"
#include <stdio.h>
#include <stdarg.h>

using namespace psi_api;


class TestCallbackContextImpl: public ICallbackContext {

public:
	TestCallbackContextImpl();

	virtual ~TestCallbackContextImpl();

	void init(
			const std::string 	&initial,
			IModel				*model,
			IComponent 			*comp);

	std::string toString();

	psshandle_t getActionNode();

	virtual int64_t getIntField(
			psshandle_t 	hndl,
			IField 			*field);

	virtual void setIntField(
			psshandle_t 	hndl,
			IField 			*field,
			int64_t 		v);

	virtual uint64_t getBitField(
			psshandle_t 	hndl,
			IField 			*field);

	virtual void setBitField(
			psshandle_t 	hndl,
			IField 			*field,
			uint64_t 		v);

	virtual bool getBoolField(
			psshandle_t 	hndl,
			IField 			*field);

	virtual void setBoolField(
			psshandle_t 	hndl,
			IField 			*field,
			bool 			v);

	virtual void *getChandleField(
			psshandle_t 	hndl,
			IField 			*field);

	virtual void setChandleField(
			psshandle_t 	hndl,
			IField 			*field,
			void 			*v);

	virtual std::string getStringField(
			psshandle_t 	hndl,
			IField 			*field);

	virtual void setStringField(
			psshandle_t 		hndl,
			IField 				*field,
			const std::string 	&v);

	/**
	 * Returns the psshandle_t handle for a field of type struct or action
	 */
	virtual psshandle_t getHandleField(
			psshandle_t 		hndl,
			IField 				*field);

	void setChandleTestMode(bool tm) { m_chandle_testmode = tm; }

private:
	class ValueNode {
	public:
		enum ValueNodeType {
			ValueNode_Scope,
			ValueNode_ScopeField,
			ValueNode_String,
			ValueNode_Bit,
			ValueNode_Int,
			ValueNode_Bool,
			ValueNode_Chandle
		};

		ValueNode(IScopeItem *scope);

		ValueNode(IField *field, uint64_t v);

		ValueNode(IField *field, int64_t v);

		ValueNode(IField *field, bool v);

		ValueNode(IField *field, void *v);

		ValueNode(IField *field, const std::string &v);

		ValueNode(IField *field);

		virtual ~ValueNode();

		std::string						m_name;
		IBaseItem						*m_type_h;

		std::vector<ValueNode *>		m_children;

		ValueNodeType					m_type;

		union {
			std::string		*str;
			uint64_t		ui64;
			int64_t			i64;
			void			*chandle;
		} m_val;
	};

private:

//	ValueNode *findNode(
//			ValueNode 						*n,
//			const std::vector<std::string> 	&path,
//			uint32_t 						idx,
//			bool 							create);

	void toString(
			std::string			&ret,
			const std::string	&name,
			ValueNode			*n);

	void log(const char *fmt, ...);

	void info(const char *fmt, ...);

	void error(const char *fmt, ...);

	void debug(const char *fmt, ...);

	static std::vector<std::string> split_path(const std::string &path);

	ValueNode *get_insert_point(const std::vector<std::string> &path);

	void add_bit_node(const std::vector<std::string> &path, uint64_t init_val);

	void add_int_node(const std::vector<std::string> &path, int64_t init_val);

	void add_bool_node(const std::vector<std::string> &path, bool init_val);

	void add_string_node(const std::vector<std::string> &path, const std::string &init_val);

	void add_chandle_node(const std::vector<std::string> &path, void *init_val);

	static uint64_t toBitValue(const std::string &str_v);

	static int64_t toIntValue(const std::string &str_v);

	static void *toChandleValue(const std::string &str_v);

private:
	IModel								*m_model;
	IComponent							*m_comp;
	ValueNode							*m_root;
	bool								m_debug_en;
	bool								m_chandle_testmode;

};


#endif /* INCLUDED_TEST_CALLBACK_CONTEXT_IMPL_H */
