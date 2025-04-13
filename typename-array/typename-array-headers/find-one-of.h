#ifndef TYPENAME_ARRAY_FIND_ONE_OF_H
#define TYPENAME_ARRAY_FIND_ONE_OF_H

#include "base.h"
#include "find.h"

template<typename array, typename array_to_find>
struct find_one_of {
private:
	template<typename helper_array, typename helper_array_to_find, typename_array_size_t index, bool is_found>
	struct find_one_of_helper {
		static constexpr typename_array_size_t indx = npos;
	};

	template<template<typename, typename...> class array_template, typename val, typename... other, typename helper_array_to_find, typename_array_size_t index>
	struct find_one_of_helper <array_template<val, other...>, helper_array_to_find, index, false> {
		static constexpr typename_array_size_t indx = find_one_of_helper<array_template<other...>, helper_array_to_find, index + 1, (find<helper_array_to_find, val>::index != -1)>::indx;
	};

	template<typename helper_array, typename helper_array_to_find, typename_array_size_t index>
	struct find_one_of_helper<helper_array, helper_array_to_find, index, true> {
		static constexpr typename_array_size_t indx = index;
	};

public:
	static constexpr typename_array_size_t index = find_one_of_helper<array, array_to_find, -1, false>::indx;
};

#endif // TYPENAME_ARRAY_FIND_ONE_OF_H