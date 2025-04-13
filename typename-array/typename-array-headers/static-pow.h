#ifndef TYPENAME_ARRAY_STATIC_POW_H
#define TYPENAME_ARRAY_STATIC_POW_H

#include "base.h"

template<typename_array_size_t val, typename_array_size_t n>
struct static_pow {
	static constexpr typename_array_size_t value = val * static_pow<val, (n - 1)>::value;
};

template<int val>
struct static_pow<val, 0> {
	static constexpr typename_array_size_t value = 1;
};

#endif // TYPENAME_ARRAY_STATIC_POW_H