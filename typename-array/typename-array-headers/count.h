#ifndef TYPENAME_ARRAY_COUNT_H
#define TYPENAME_ARRAY_COUNT_H

#include "base.h"

template<typename array, typename value_to_count>
struct count {
private:
	template<typename helper_array, typename helper_value_to_count, typename_array_size_t appearances>
	struct count_helper {
		static constexpr typename_array_size_t counter = appearances;
	};

	template<template<typename, typename...> class templ, typename value, typename... other, typename helper_value_to_count, typename_array_size_t appearances>
	struct count_helper<templ<value, other...>, helper_value_to_count, appearances> {
		static constexpr typename_array_size_t counter = count_helper<templ<other...>, helper_value_to_count, appearances>::counter;
	};

	template<template<typename, typename...> class templ, typename... other, typename helper_value_to_count, typename_array_size_t appearances>
	struct count_helper<templ<helper_value_to_count, other...>, helper_value_to_count, appearances> {
		static constexpr typename_array_size_t counter = count_helper<templ<other...>, helper_value_to_count, (appearances + 1)>::counter;
	};

public:
	static constexpr typename_array_size_t counter = count_helper<array, value_to_count, 0>::counter;
};

#endif // TYPENAME_ARRAY_COUNT_H