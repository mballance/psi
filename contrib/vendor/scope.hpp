
#ifndef INCLUDED_SCOPE_H
#include "scope.h"
#endif /* INCLUDED_SCOPE_H */
#include <typeinfo>

namespace pss {

template <class T> scope::scope(T *t) : pss::vendor::scope_impl(
		&typeid(T), t, false, false, "", 0) {

}

}

