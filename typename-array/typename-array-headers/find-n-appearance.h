#ifndef TYPENAME_ARRAY_FIND_N_APPEARANCE_H
#define TYPENAME_ARRAY_FIND_N_APPEARANCE_H

#include "base.h"

template<typename array, typename value_to_find, typename_array_size_t count>
struct find_n_appearance {
private:
	template<typename helper_array, typename helper_value_to_find, typename_array_size_t helper_count, typename_array_size_t index, bool dummy>
	struct find_n_appearance_helper {
		static constexpr typename_array_size_t indx = npos;
	};

	template<template<typename, typename...> class templ, typename value, typename helper_value_to_find, typename... other, typename_array_size_t helper_count, typename_array_size_t index>
	struct find_n_appearance_helper<templ<value, other...>, helper_value_to_find, helper_count, index, true> {
		static constexpr typename_array_size_t indx = find_n_appearance_helper<templ<other...>, helper_value_to_find, helper_count, (index + 1), true>::indx;
	};

	template<template<typename, typename...> class templ, typename helper_value_to_find, typename... other, typename_array_size_t helper_count, typename_array_size_t index>
	struct find_n_appearance_helper<templ<helper_value_to_find, other...>, helper_value_to_find, helper_count, index, true> {
		static constexpr typename_array_size_t indx = find_n_appearance_helper<templ<other...>, helper_value_to_find, (helper_count - 1), (index + 1), ((helper_count - 1) != 0)>::indx;
	};

	template<template<typename...> class templ, typename... other, typename helper_value_to_find, typename_array_size_t index>
	struct find_n_appearance_helper<templ<other...>, helper_value_to_find, 0, index, false> {
		static constexpr typename_array_size_t indx = (index - 1);
	};

public:
	static constexpr typename_array_size_t index = find_n_appearance_helper<array, value_to_find, count, 0, true>::indx;
};

#endif // TYPENAME_ARRAY_FIND_N_APPEARANCE_H