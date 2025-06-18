#ifndef TYPENAME_ARRAY_INSERT_H
#define TYPENAME_ARRAY_INSERT_H

#include "base.h"

template<typename_array_size_type insert_index, typename array, typename new_type>
struct insert {
private:
	template<typename_array_size_type index, typename helper_array, typename helper_new_type>
	struct insert_helper;

	template<template<typename...> class array_template, typename... other, typename helper_new_type>
	struct insert_helper<insert_index, array_template<other...>, helper_new_type> {
		using new_array = typename combine<typename_array<helper_new_type>, array_template<other...>>::new_array;
	};

	template<typename_array_size_type index, template<typename, typename...> class array_template, typename helper_new_type, typename value, typename... other>
	struct insert_helper<index, array_template<value, other...>, helper_new_type> {
		using new_array = typename combine<
			typename_array<value>, typename insert_helper<index + 1, array_template<other...>, helper_new_type>::new_array
		>::new_array;
	};

public:
	using new_array = typename insert_helper<0, array, new_type>::new_array;
};

#endif // TYPENAME_ARRAY_INSERT_H