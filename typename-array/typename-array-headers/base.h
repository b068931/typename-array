#ifndef TYPENAME_ARRAY_BASE_H
#define TYPENAME_ARRAY_BASE_H

#include <type_traits>

using typename_array_size_t = long long;
constexpr typename_array_size_t npos = -1;

template<typename... arguments>
struct typename_array {
	static constexpr typename_array_size_t size = sizeof... (arguments);

	template<template<typename... other> class other_template>
	using acquire = other_template<arguments...>;
};

template<typename first_array, typename second_array>
struct combine;

template<template<typename...> class array_template, typename ...first_array_arguments, typename ...second_array_arguments>
struct combine<array_template<first_array_arguments...>, array_template<second_array_arguments...>> {
	using new_array = array_template<first_array_arguments..., second_array_arguments...>;
};

#endif // TYPENAME_ARRAY_BASE_H