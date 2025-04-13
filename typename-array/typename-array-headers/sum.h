#ifndef TYPENAME_ARRAY_SUM_H
#define TYPENAME_ARRAY_SUM_H

#include "base.h"

template<typename array, template<typename> class funct, typename return_type>
struct sum {
private:
	template<typename helper_array, template<typename> class helper_funct>
	struct sum_helper {
		static constexpr return_type new_value{ 0 };
	};

	template<template<typename> class templ, typename value, template<typename> class helper_funct>
	struct sum_helper<templ<value>, helper_funct> {
		static constexpr return_type new_value = helper_funct<value>::value;
	};

	template<template<typename, typename...> class templ, typename value, typename... other, template<typename> class helper_funct>
	struct sum_helper<templ<value, other...>, helper_funct> {
		static constexpr decltype(auto) new_value = helper_funct<value>::value + sum_helper<templ<other...>, helper_funct>::new_value;
	};

public:
	static constexpr decltype(auto) new_value = sum_helper<array, funct>::new_value;
};

#endif // TYPENAME_ARRAY_SUM_H