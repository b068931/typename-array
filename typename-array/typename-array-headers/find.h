#ifndef TYPENAME_ARRAY_FIND_H
#define TYPENAME_ARRAY_FIND_H

#include "base.h"

template<typename array, typename val_to_find>
struct find {
private:
	template<typename helper_array, typename find, typename_array_size_t index>
	struct find_helper {
		static constexpr typename_array_size_t indx = npos;
	};

	template<template<typename, typename...> class array_template, typename val, typename... other, typename find, typename_array_size_t index>
	struct find_helper<array_template<val, other...>, find, index> {
		static constexpr typename_array_size_t indx = find_helper<array_template<other...>, find, index + 1>::indx;
	};

	template<template<typename, typename...> class array_template, typename... other, typename find, typename_array_size_t index>
	struct find_helper<array_template<find, other...>, find, index> {
		static constexpr typename_array_size_t indx = index;
	};

public:
	static constexpr typename_array_size_t index = find_helper<array, val_to_find, 0>::indx;
};


#endif // TYPENAME_ARRAY_FIND_H