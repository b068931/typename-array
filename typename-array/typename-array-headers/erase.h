#ifndef TYPENAME_ARRAY_ERASE_H
#define TYPENAME_ARRAY_ERASE_H

#include "base.h"

template<typename_array_size_type index_to_erase, typename array>
struct erase {
public:
	template<typename_array_size_type index, typename helper_array>
	struct erase_helper;

	template<template<typename, typename...> class array_template, typename type, typename... other>
	struct erase_helper<index_to_erase, array_template<type, other...>> {
		using new_array = typename_array<other...>;
	};

	template<typename_array_size_type index, template<typename, typename...> class array_template, typename type, typename... other>
	struct erase_helper<index, array_template<type, other...>> {
		using new_array = typename combine<typename_array<type>, typename erase_helper<index + 1, typename_array<other...>>::new_array>::new_array;
	};

public:
	using new_array = typename erase_helper<0, array>::new_array;
};

#endif // TYPENAME_ARRAY_ERASE_H
