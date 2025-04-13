#ifndef TYPENAME_ARRAY_FIND_PRIORITY_H
#define TYPENAME_ARRAY_FIND_PRIORITY_H

#include "base.h"
#include "find.h"

template<typename array, typename array_to_find>
struct find_priority {
private:
	template<typename helper_array, typename helper_array_to_find>
	struct find_priority_helper {
		static constexpr typename_array_size_t indx = npos;
	};

	template<typename_array_size_t val>
	struct cont {
		static constexpr typename_array_size_t indx = val;
	};

	template<template<typename, typename...> class templ, typename val, typename... other, typename helper_array>
	struct find_priority_helper<helper_array, templ<val, other...>> {
		using value_type = typename std::conditional<
			(find<helper_array, val>::index == -1),
			find_priority_helper<helper_array, templ<other...>>,
			cont<find<helper_array, val>::index>
		>::type;

		static constexpr typename_array_size_t indx = value_type::indx;
	};

public:
	static constexpr typename_array_size_t index = find_priority_helper<array, array_to_find>::indx;
};

#endif // TYPENAME_ARRAY_FIND_PRIORITY_H