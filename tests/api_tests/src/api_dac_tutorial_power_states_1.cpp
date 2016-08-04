/*
 * api_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 13, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

void build(IModel *model) {

	IStruct *power_state_s = model->mkStruct(
			"power_state_s", IStruct::State, 0);

	IField *dmn_A = model->mkField("dmn_A",
			model->mkScalarType(IScalarType::ScalarType_Bit, 1, 0),
			IField::FieldAttr_Rand);
	IField *dmn_B = model->mkField("dmn_B",
			model->mkScalarType(IScalarType::ScalarType_Bit, 1, 0),
			IField::FieldAttr_Rand);
	IField *dmn_C = model->mkField("dmn_C",
			model->mkScalarType(IScalarType::ScalarType_Bit, 1, 0),
			IField::FieldAttr_Rand);

	// ...

	power_state_s->add(dmn_A);
	power_state_s->add(dmn_B);
	power_state_s->add(dmn_C);

	model->getGlobalPackage()->add(power_state_s);

}



