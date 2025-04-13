#ifndef TYPENAME_ARRAY_REPLACE_H
#define TYPENAME_ARRAY_REPLACE_H

#include "base.h"

template<typename_array_size_t replace_index, typename array, typename new_type>
struct replace {
private:
	template<typename_array_size_t index, typename helper_array, typename helper_new_type>
	struct replace_helper;

	template<template<typename, typename...> class array_template, typename val, typename... other, typename helper_new_type>
	struct replace_helper<replace_index, array_template<val, other...>, helper_new_type> {
		using new_array = array_template<helper_new_type, other...>;
	};

	template<typename_array_size_t index, template<typename, typename...> class array_template, typename val, typename... other, typename helper_new_type>
	struct replace_helper<index, array_template<val, other...>, helper_new_type> {
		using new_array = typename combine<typename_array<val>, typename replace_helper<index + 1, array_template<other...>, helper_new_type>::new_array>::new_array;
	};

public:
	using new_array = typename replace_helper<0, array, new_type>::new_array;
};

#endif // TYPENAME_ARRAY_REPLACE_H