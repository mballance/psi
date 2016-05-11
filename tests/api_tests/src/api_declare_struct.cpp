/*
 * api_declare_struct.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

void build_model(IModel *model) {
	// memory struct data_s
	IStruct *data_s = model->mkStruct("data_s", IStruct::Memory, 0);

	// rand bit[7:0] data;
	IField *data = model->mkField("data",
			model->mkScalarType(IScalarType::ScalarType_Bit, 7, 0),
			IField::FieldAttr_Rand);
	data_s->add(data);

	// rand bit[31:0] address;
	IField *address = model->mkField("address",
			model->mkScalarType(IScalarType::ScalarType_Bit, 31, 0),
			IField::FieldAttr_Rand);
	data_s->add(address);

	data_s->add(model->mkConstraintBlock("", model->mkConstraintExpr(
		model->mkBinExpr(
			model->mkBinExpr(address->getFieldRef(),
					IBinaryExpr::BinOp_GE, model->mkBitLiteral(0x1000)),
				IBinaryExpr::BinOp_AndAnd,
			model->mkBinExpr(address->getFieldRef(),
					IBinaryExpr::BinOp_LE, model->mkBitLiteral(0x1FFF))
			))
		)
	);

	model->getGlobalPackage()->add(data_s);
}

