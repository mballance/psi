/*
 * InlineExecUtil.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#include "InlineExecUtil.h"
#include "ActionImp.h"
#include "ComponentImp.h"
#include "StructImp.h"

#include <stdio.h>

namespace pss {

InlineExecUtil::InlineExecUtil(BaseItemImp *field) {
	m_field = field;
}

InlineExecUtil::~InlineExecUtil() {
	// TODO Auto-generated destructor stub
}

bool InlineExecUtil::find_model_hndl_level(
	BaseItemImp			*field,
	IModel				*&model,
	psshandle_t			&hndl,
	uint32_t			&level) {
	BaseItemImp *s = field;
	level = 0;
	model = 0;
	hndl = 0;

	// First, find the model and object handle
	while (s) {
		// See if we've reached the active scope
		if (s->getObjectType() == BaseItemImp::TypeAction) {
			model = static_cast<ActionImp *>(s)->getModel();
			hndl  = static_cast<ActionImp *>(s)->getHandle();
		} else if (s->getObjectType() == BaseItemImp::TypeStruct) {
			model = static_cast<StructImp *>(s)->getModel();
			hndl  = static_cast<StructImp *>(s)->getHandle();
		}

		if (model) {
			break;
		}
		s = s->getParent();
		level++;
	}

	return (model)?true:false;
}

bool InlineExecUtil::update_lookup_path() {
	BaseItemImp *s = m_field;
	uint32_t level = 0;
	BaseItemImp *lookup_scope = 0;
	std::vector<std::string> path;

	// Yep... Build up a list of names we need to lookup
	m_field_path.clear();

	IModel *model = 0;
	psshandle_t hndl = 0;

	while (s) {
		level++;
		// See if we've reached the active scope
		if (s->getObjectType() == BaseItemImp::TypeAction) {
			model = static_cast<ActionImp *>(s)->getModel();
			hndl  = static_cast<ActionImp *>(s)->getHandle();
		} else if (s->getObjectType() == BaseItemImp::TypeStruct) {
			model = static_cast<StructImp *>(s)->getModel();
			hndl  = static_cast<StructImp *>(s)->getHandle();
		}
		NamedBaseItemImp *ni = dynamic_cast<NamedBaseItemImp *>(s);

		if (ni) {
			path.insert(path.begin(), ni->getName());
		} else {
			fprintf(stdout, "Error: unnamed item %d\n", s->getObjectType());
		}

		if (model) {
			lookup_scope = s;
			break;
		}
		s = s->getParent();
	}

	if (lookup_scope) {
		IScopeItem *scope = 0;

		if (lookup_scope->getObjectType() == BaseItemImp::TypeStruct) {
			// Structs can appear
			StructImp *str = static_cast<StructImp *>(lookup_scope);
		} else if (lookup_scope->getObjectType() == BaseItemImp::TypeAction) {
			// Actions always appear inside a component
			// Components are always top-level items
			ActionImp *a = static_cast<ActionImp *>(lookup_scope);
			ComponentImp *c = static_cast<ComponentImp *>(a->getParent());

			for (std::vector<IBaseItem *>::const_iterator it=model->getItems().begin();
					it!=model->getItems().end(); it++) {
				IBaseItem *t = *it;
				if (t->getType() == IBaseItem::TypeComponent &&
						static_cast<IComponent *>(t)->getName() == c->getName()) {
					scope = static_cast<IComponent *>(t);
					break;
				}
			}

			if (!scope) {
				fprintf(stdout, "Error: Failed to find component %s\n", c->getName().c_str());
			}

			for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
					it!=scope->getItems().end(); it++) {
				IBaseItem *t = *it;

				if (t->getType() == IBaseItem::TypeAction &&
						static_cast<IAction *>(t)->getName() == a->getName()) {
					scope = static_cast<IAction *>(t);
					break;
				}
			}
		}


		// Walk back down, using the model API to lookup Model fields
//		fprintf(stdout, "Lookup scope: %d %s\n", lookup_scope->getObjectType(),
//				(static_cast<NamedBaseItemImp *>(lookup_scope))?
//						static_cast<NamedBaseItemImp *>(lookup_scope)->getName().c_str():
//						"NULL");

		// Walk back down,
		for (uint32_t i=1; i<path.size(); i++) {
			fprintf(stdout, "  path=%s\n", path.at(i).c_str());
			const std::string &path_e = path.at(i);

			IField *f = 0;

			for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
					it!=scope->getItems().end(); it++) {
				IBaseItem *t = *it;

				if (t->getType() == IBaseItem::TypeField &&
						static_cast<IField *>(t)->getName() == path_e) {
					f = static_cast<IField *>(t);
					break;
				}
			}

			if (f) {
				m_field_path.push_back(f);

				scope = dynamic_cast<IScopeItem *>(f->getDataType());

				if (i+1 < path.size() && scope) {
					fprintf(stdout, "Error: data-type of %s is not a scope\n", path_e.c_str());
					break;
				}
			} else {
				fprintf(stdout, "Error: Failed to find field %s\n", path_e.c_str());
			}
		}

	} else {
		fprintf(stdout, "Error: failed to find target scope\n");
	}

	return true;
}

uint64_t InlineExecUtil::getBitValue() {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	return ctxt->getBitField(hndl, field);
}

void InlineExecUtil::setBitValue(uint64_t v) {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	ctxt->setBitField(hndl, field, v);
}

int64_t InlineExecUtil::getIntValue() {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	return ctxt->getIntField(hndl, field);
}

void InlineExecUtil::setIntValue(int64_t v) {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	ctxt->setIntField(hndl, field, v);
}

bool InlineExecUtil::getBoolValue() {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	return ctxt->getBoolField(hndl, field);
}

void InlineExecUtil::setBoolValue(bool v) {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	ctxt->setBoolField(hndl, field, v);
}

void *InlineExecUtil::getChandleValue() {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	return ctxt->getChandleField(hndl, field);
}

void InlineExecUtil::setChandleValue(void *v) {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	ctxt->setChandleField(hndl, field, v);
}

std::string InlineExecUtil::getStringValue() {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	return ctxt->getStringField(hndl, field);
}

void InlineExecUtil::setStringValue(const std::string &v) {
	ICallbackContext *ctxt;
	psshandle_t hndl = 0;
	IField *field = 0;

	get_hndl_ctxt_field(ctxt, hndl, field);

	ctxt->setStringField(hndl, field, v);
}

void InlineExecUtil::get_hndl_ctxt_field(
		ICallbackContext		*&ctxt,
		psshandle_t				&hndl,
		IField					*&field) {
	uint32_t level = 0;
	IModel *model = 0;

	// First, find the model and object handle
	find_model_hndl_level(m_field, model, hndl, level);

	if (level != m_field_path.size()) {
		update_lookup_path();
	}

	ctxt = model->getCallbackContext();
	for (uint32_t i=0; i<m_field_path.size(); i++) {
		if (i+1 < m_field_path.size()) {
			// lookup the new hndl
			hndl = ctxt->getHandleField(hndl, m_field_path.at(i));
		} else {
			// This is the target
			field = m_field_path.at(i);
		}
	}
}

} /* end namespace pss */
