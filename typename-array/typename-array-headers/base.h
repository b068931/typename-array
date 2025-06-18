#ifndef TYPENAME_ARRAY_BASE_H
#define TYPENAME_ARRAY_BASE_H

#include <type_traits>

/// <summary>
/// Type used for array indexing and size representation.
/// </summary>
using typename_array_size_type = long long;

/// <summary>
/// Special value indicating "no position" or "not found" in typename arrays.
/// </summary>
constexpr typename_array_size_type npos = -1;

/// <summary>
/// A compile-time container for a sequence of types.
/// </summary>
/// <typeparam name="arguments">The types to be stored in this array.</typeparam>
template<typename... arguments>
struct typename_array {
    /// <summary>
    /// The number of types contained in this array.
    /// </summary>
    static constexpr typename_array_size_type size = sizeof... (arguments);

    /// <summary>
    /// Transfers the types in this array to another template.
    /// </summary>
    /// <typeparam name="other_template">The destination template to receive the types.</typeparam>
    template<template<typename... other> class other_template>
    using acquire = other_template<arguments...>;
};

/// <summary>
/// Forward declaration for combining two typename arrays.
/// </summary>
/// <typeparam name="first_array">The first array of types.</typeparam>
/// <typeparam name="second_array">The second array of types.</typeparam>
template<typename first_array, typename second_array>
struct combine;

/// <summary>
/// Specialized implementation for combining two typename arrays.
/// Creates a new typename array that contains all types from both input arrays,
/// preserving their original order (first array's types followed by second array's types).
/// </summary>
/// <typeparam name="array_template">The template class of both arrays (typically typename_array).</typeparam>
/// <typeparam name="first_array_arguments">Types from the first array.</typeparam>
/// <typeparam name="second_array_arguments">Types from the second array.</typeparam>
template<template<typename...> class array_template, typename ...first_array_arguments, typename ...second_array_arguments>
struct combine<array_template<first_array_arguments...>, array_template<second_array_arguments...>> {
    /// <summary>
    /// The resulting array type after combination.
    /// </summary>
    using new_array = array_template<first_array_arguments..., second_array_arguments...>;
};

#endif // TYPENAME_ARRAY_BASE_H