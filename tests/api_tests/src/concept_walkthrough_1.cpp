/*
 * concept_walkthrough.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

template <class T> class TypeDecl {
public:
	TypeDecl() {
		fprintf(stdout, "TypeDecl: static\n");
		m_hndl = new T();
	}

private:
	T				*m_hndl;
};

class data_s : public MemoryStruct {
public:
	TypeRgy<data_s>		type_id{this};

	Rand<Bit<7,0>>		psi_field(data);
	Rand<Bit<31,0>>		psi_field(address);

	data_s(Type *p=0, psi_name name="data_s") : MemoryStruct(p, name) { }

	Constraint address_c {this, address >= 0x1000 && address <= 0x1FFF};

	// Register this type definition
};
TypeDecl<data_s> _data_s;

static class rw_comp : public Component {
public:
	TypeRgy<rw_comp>		type_id{this};

	rw_comp(Type *p=0, psi_name name="rw_comp") : Component(p, name) { }

	class processor_s : public ResourceStruct {
	public:
		TypeRgy<processor_s>		type_id{this};

		processor_s(Type *p=0, psi_name name="processor_s") : ResourceStruct(p, name) { }

		Constraint resource_c {this, instance_id == 1};

	} processor_sT {this};

	class write_data : public Action {
	public:
		TypeRgy<write_data>		type_id{this};

		write_data(Type *p=0, psi_name name="write_data") : Action(p, name) { }

		Output<data_s>			psi_field(out_data);
		Lock<processor_s>		psi_field(proc);

	} write_dataT {this};

	class read_data : public Action {
	public:
		TypeRgy<read_data>		type_id{this};

		read_data(Type *p=0, const std::string &name="read_data") : Action(p, name) { }

		Input<data_s>			psi_field(in_data);
		Lock<processor_s>		psi_field(proc);
	} read_dataT {this};

} rw_compT;

class top_comp : public Component {
public:
	TypeRgy<top_comp>		type_id{this};

	top_comp(Type *p=0, psi_name name="top_comp") : Component(p, name) { }

	class my_test2 : public Action {
	public:
		TypeRgy<my_test2>		type_id{this};

		my_test2(Type *p=0, psi_name name="my_test2") : Action(p, name) { }

		// Action instance needs to know the details of its type. This is
		// provided via a type-definition reference (eg _rw_comp._write_data)
		Field<rw_comp::write_data>		psi_field(wd1);
		Field<rw_comp::read_data>		psi_field(rd1);
		Field<rw_comp::write_data>		psi_field(wd2);
		Field<rw_comp::read_data>		psi_field(rd2);

		// Only a single graph is permitted per action
		Graph graph {this,
			(wd1, rd1, wd2, rd2)
		};

		Constraint addr_c {this, rd1.in_data.address != rd2.in_data.address };

	} my_test2T {this}; // Complete registration of this type

} top_compT;

class c_methods : public Package {
public:
	TypeRgy<c_methods>		type_id{this};

	c_methods(Type *p=0, psi_name name="c_methods") : Package(p, name) { }

	// Prototypes for import functions
	Import do_write {this, "do_write",
		(Bit<31,0>("addr"), Bit<31,0>("data"))
	};

	Import do_check {this, "do_check",
		(Bit<31,0>("addr"), Bit<31,0>("data"))
	};

} c_methodsT;

class c_code : public Package {
public:
	TypeRgy<c_code>		type_id{this};

	c_code(Type *p=0, psi_name name="c_code") : Package(p, name) { }

	// Declares an extension of 'write_data' to layer in the implementation
	class write_data_ext : public ExtendAction<rw_comp::write_data> {
	public:

		write_data_ext(Type *p=0) : ExtendAction(p) { }

		// Example of a target-template exec block
		Exec do_write_body {this, Exec::Body, "C", R"(
				do_write({{address}}, {{data}}
				)"
		};

		Exec do_write_body_native {this, Exec::Body,
			c_methodsT.do_write((out_data.address, out_data.data))
		};
	} write_data_extT {this};

	class read_data_ext : public ExtendAction<rw_comp::read_data> {
	public:

		read_data_ext(Type *p=0) : ExtendAction(p) {}

		Exec do_check_body_native {this, Exec::Body,
			c_methodsT.do_check((in_data.address, in_data.data))
		};
	} read_data_extT {this};

} c_codeT;

