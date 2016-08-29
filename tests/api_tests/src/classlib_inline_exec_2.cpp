/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"
#include "PsiUtil.h"

using namespace psi::apps;

void exec_model(IModel *model) {
	// Lookup and invoke inline execs
	IComponent *top = 0;

	IPackage *pkg = model->getGlobalPackage();
	for (std::vector<IBaseItem *>::const_iterator it=model->getItems().begin();
			it!=model->getItems().end(); it++) {
		INamedItem *ni = PSIUtil::toNamedItem((*it));
		fprintf(stdout, "pkg: it=%p ni=%p name=%s\n", *it, ni,
				(ni)?ni->getName().c_str():"null");
		fflush(stdout);
		if (ni && ni->getName() == "top") {
			top = static_cast<IComponent *>(*it);
			break;
		}
	}

	IAction *entry_point = 0;
	for (std::vector<IBaseItem *>::const_iterator it=top->getItems().begin();
			it!=top->getItems().end(); it++) {
		INamedItem *ni = PSIUtil::toNamedItem((*it));
		if (ni && ni->getName() == "entry_point") {
			entry_point = static_cast<IAction *>(*it);
			break;
		}
	}

	IExec *pre_solve=0, *post_solve=0;
	for (std::vector<IBaseItem *>::const_iterator it=entry_point->getItems().begin();
			it!=entry_point->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeExec) {
			IExec *exec = static_cast<IExec *>(t);
			if (exec->getExecKind() == IExec::PreSolve) {
				pre_solve = exec;
			} else if (exec->getExecKind() == IExec::PostSolve) {
				post_solve = exec;
			}
		}
	}

	pre_solve->getInlineExec()->exec(0, 0);
	post_solve->getInlineExec()->exec(0, 0);
}

int refmodel_get_next_value() {
	return 27;
}

class methods_pkg : public Package {
public:
	pss_package_ctor(methods_pkg);

	ImportFunc my_func {this, "my_func",
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	ImportFunc my_func2 {this, "my_func2", Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

};
pss_global_type(methods_pkg);

class top : public Component {
public:
	pss_component_ctor(top);

	class entry_point : public Action {
	public:
		pss_action_ctor(entry_point);

		Rand<Bit<7,0>>		pss_field(p1);
		Rand<Bit<31,0>>		pss_field(p2);
		Rand<Bit<31,0>>		pss_field(p3);
		Field<Bit<31,0>>	pss_field(p4);
		Field<Bit<31,0>>	pss_field(p5);

		Exec pre_solve_e {this, Exec::PreSolve, { p4 } };

		Exec post_solve_e {this, Exec::PostSolve, { p5 } };

		void pre_solve() {
			// Set p4 based on calling a generation-time method

			// Context will be set for 'this' action
			// - build type path, searching up, until we reach our type context
			// - Composite types will be represented by the <type> handle, not the
			//   <field> handle. Must fix up
			// - Must associate IField handles with each object on the path. While
			//   the object-context handles may change over time, the Type handles
			//   will not.
			// - To execute an accessor function:
			//   - Traverse up to the <context> node
			//   - Traverse down, obtaining psshandle_t handles
			//   - Call the accessor method
			fprintf(stdout, "Note: pre_solve\n");
			p4.set(refmodel_get_next_value());
		}

		void post_solve() {
			// Set p5 based on a calculated value
			fprintf(stdout, "Note: post_solve\n");
//			p5.set(p1.get() + p2.get());
		}
	};
	pss_type(entry_point);

};
pss_global_type(top);


