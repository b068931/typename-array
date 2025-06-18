#ifndef TYPENAME_ARRAY_GET_H
#define TYPENAME_ARRAY_GET_H

#include "base.h"

template<typename_array_size_type index, typename array>
struct get {
private:
	template<typename_array_size_type counter, typename helper_array>
	struct get_helper;

	template<template<typename, typename...> class array_template, typename val, typename... other>
	struct get_helper<0, array_template<val, other...>> {
		using value = val;
	};

	template<typename_array_size_type counter, template<typename, typename...> class array_template, typename val, typename... other>
	struct get_helper<counter, array_template<val, other...>> {
		using value = typename get_helper<counter - 1, typename_array<other...>>::value;
	};

public:
	using value = typename get_helper<index, array>::value;
};

#endif // TYPENAME_ARRAY_GET_H