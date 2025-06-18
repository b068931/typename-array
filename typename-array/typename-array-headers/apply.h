#ifndef TYPENAME_ARRAY_APPLY_H
#define TYPENAME_ARRAY_APPLY_H

#include "base.h"

/// <summary>
/// Applies a function template to each type in an array, producing a new array with transformed types.
/// </summary>
/// <typeparam name="array">The source typename array containing types to transform.</typeparam>
/// <typeparam name="funct">A template that transforms each type, receiving the type and its index. Must define ::new_type.</typeparam>
template<typename array, template<typename, typename_array_size_type> class funct>
struct apply {
private:
    /// <summary>
    /// Helper for applying the function to each element in the array.
    /// </summary>
    /// <typeparam name="helper_array">The array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_funct">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<typename helper_array, template<typename, typename_array_size_type> class helper_funct, typename_array_size_type index>
    struct apply_helper;

    /// <summary>
    /// Specialization for processing the last element in the array.
    /// </summary>
    /// <typeparam name="templ">The template of the array.</typeparam>
    /// <typeparam name="value">The type of the last element.</typeparam>
    /// <typeparam name="helper_funct">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<template<typename> class templ, typename value, template<typename, typename_array_size_type> class helper_funct, typename_array_size_type index>
    struct apply_helper<templ<value>, helper_funct, index> {
        /// <summary>
        /// The resulting array with a single transformed type.
        /// </summary>
        using new_array = typename_array<typename helper_funct<value, index>::new_value>;
    };

    /// <summary>
    /// Specialization for processing an array with multiple elements.
    /// Recursively applies the function to each element and combines the results.
    /// </summary>
    /// <typeparam name="templ">The template of the array.</typeparam>
    /// <typeparam name="other">The remaining types in the array.</typeparam>
    /// <typeparam name="value">The current type being processed.</typeparam>
    /// <typeparam name="helper_funct">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<template<typename, typename...> class templ, typename... other, typename value, template<typename, typename_array_size_type> class helper_funct, typename_array_size_type index>
    struct apply_helper<templ<value, other...>, helper_funct, index> {
        /// <summary>
        /// The array resulting from combining the transformed current element with
        /// recursively processed remaining elements.
        /// </summary>
        using new_array = typename combine<
            typename_array<typename helper_funct<value, index>::new_value>,
            typename apply_helper<templ<other...>, helper_funct, (index + 1)>::new_array
        >::new_array;
    };

public:
    /// <summary>
    /// The resulting array after applying the function to each element of the input array.
    /// </summary>
    using new_array = typename apply_helper<array, funct, 0>::new_array;
};

#endif // TYPENAME_ARRAY_APPLY_H