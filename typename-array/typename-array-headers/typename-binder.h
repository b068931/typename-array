#ifndef TYPENAME_ARRAY_TYPENAME_BINDER_H
#define TYPENAME_ARRAY_TYPENAME_BINDER_H

#include "base.h"
#include "replace.h"
#include "insert.h"
#include "find.h"
#include "left-to-right.h"
#include "get.h"

template<typename_array_size_t index>
struct placeholder {};

template<template<typename, typename...> class templ, typename... other>
struct typename_binder {
private:
	template<typename_array_size_t index, typename array, typename val>
	struct dispatch {
		using value = typename replace<index, array, val>::new_array;
	};

	template<typename array, typename val>
	struct dispatch<npos, array, val> {
		using value = typename insert<array::size, array, val>::new_array;
	};

	template<typename_array_size_t index, typename_array_size_t end, typename array>
	struct bind_helper {
		using temp = typename bind_helper<index + 1, end, array>::bind;
		using bind = typename dispatch<find<temp, placeholder<index>>::index, temp, typename get<index, array>::value>::value;
	};

	template<typename_array_size_t end, typename array>
	struct bind_helper<end, end, array> {
		using bind = typename dispatch<find<typename_array<other...>, placeholder<end>>::index, typename_array<other...>, typename get<end, array>::value>::value;
	};

public:
	template<typename... additional_other>
	using bind = typename bind_helper<0, typename_array<additional_other...>::size - 1, typename left_to_right<typename_array<additional_other...>>::new_array>::bind::template acquire<templ>;
};


#endif // TYPENAME_ARRAY_TYPENAME_BINDER_H