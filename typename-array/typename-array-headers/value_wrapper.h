#ifndef TYPENAME_ARRAY_VALUE_H
#define TYPENAME_ARRAY_VALUE_H

#include "base.h"

template<auto val>
struct value_wrapper {
	static constexpr decltype(val) get_value = val;
};

#endif // TYPENAME_ARRAY_VALUE_H
