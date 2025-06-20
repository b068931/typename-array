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
/// <typeparam name="arguments_type">The types to be stored in this array.</typeparam>
template<typename... arguments_type>
struct typename_array {
    /// <summary>
    /// The number of types contained in this array.
    /// </summary>
    static constexpr typename_array_size_type size = sizeof... (arguments_type);

    /// <summary>
    /// Transfers the types in this array to another template.
    /// </summary>
    /// <typeparam name="other_template">The destination template to receive the types.</typeparam>
    template<template<typename... other_type> class other_template>
    using acquire = other_template<arguments_type...>;
};

/// <summary>
/// Forward declaration for combining two typename arrays.
/// </summary>
/// <typeparam name="first_array_type">The first array of types.</typeparam>
/// <typeparam name="second_array_type">The second array of types.</typeparam>
template<typename first_array_type, typename second_array_type>
struct combine;

/// <summary>
/// Specialized implementation for combining two typename arrays.
/// Creates a new typename array that contains all types from both input arrays,
/// preserving their original order (first array's types followed by second array's types).
/// </summary>
/// <typeparam name="array_template">The template class of both arrays (typically typename_array).</typeparam>
/// <typeparam name="first_array_arguments_type">Types from the first array.</typeparam>
/// <typeparam name="second_array_arguments_type">Types from the second array.</typeparam>
template<template<typename...> class array_template, typename... first_array_arguments_type, typename... second_array_arguments_type>
struct combine<array_template<first_array_arguments_type...>, array_template<second_array_arguments_type...>> {
    /// <summary>
    /// The resulting array type after combination.
    /// </summary>
    using new_array = array_template<first_array_arguments_type..., second_array_arguments_type...>;
};

#endif // TYPENAME_ARRAY_BASE_H