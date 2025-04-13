#ifndef TYPENAME_ARRAY_APPLY_H
#define TYPENAME_ARRAY_APPLY_H

#include "base.h"

template<typename array, template<typename, typename_array_size_t> class funct>
struct apply {
private:
	template<typename helper_array, template<typename, typename_array_size_t> class helper_funct, typename_array_size_t index>
	struct apply_helper;

	template<template<typename> class templ, typename value, template<typename, typename_array_size_t> class helper_funct, typename_array_size_t index>
	struct apply_helper<templ<value>, helper_funct, index> {
		using new_array = typename_array<typename helper_funct<value, index>::new_value>;
	};

	template<template<typename, typename...> class templ, typename... other, typename value, template<typename, typename_array_size_t> class helper_funct, typename_array_size_t index>
	struct apply_helper<templ<value, other...>, helper_funct, index> {
		using new_array = typename combine<
			typename_array<typename helper_funct<value, index>::new_value>,
			typename apply_helper<templ<other...>, helper_funct, (index + 1)>::new_array
		>::new_array;
	};

public:
	using new_array = typename apply_helper<array, funct, 0>::new_array;
};

#endif // TYPENAME_ARRAY_APPLY_H