#ifndef TYPENAME_ARRAY_CHECK_FOR_ALLOWED_TYPES_H
#define TYPENAME_ARRAY_CHECK_FOR_ALLOWED_TYPES_H

#include "base.h"
#include "find.h"

template<typename array, typename allowed_types>
struct check_for_allowed_types {
private:
	template<typename helper_array, typename helper_allowed_types, bool is_continue>
	struct check_for_allowed_types_helper {
		static constexpr decltype(auto) is_valid = false;
	};

	template<typename helper_array, typename helper_allowed_types>
	struct check_for_allowed_types_helper<helper_array, helper_allowed_types, true> {
		static constexpr decltype(auto) is_valid = true;
	};

	template<template<typename, typename...> class templ, typename value, typename... other, typename helper_allowed_types>
	struct check_for_allowed_types_helper<templ<value, other...>, helper_allowed_types, true> {
		static constexpr decltype(auto) is_valid = check_for_allowed_types_helper<templ<other...>, helper_allowed_types, (find<helper_allowed_types, value>::index != npos)>::is_valid;
	};

public:
	static constexpr decltype(auto) is_valid = check_for_allowed_types_helper<array, allowed_types, true>::is_valid;
};

#endif // TYPENAME_ARRAY_CHECK_FOR_ALLOWED_TYPES_H