#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_APPLY_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_APPLY_H

#include "base.h"

/// <summary>
/// Applies a function template to each type in an array, producing a new array with transformed types.
/// </summary>
/// <typeparam name="array_type">The source typename array containing types to transform.</typeparam>
/// <typeparam name="functor_template">A template that transforms each type, receiving the type and its index. Must define ::new_type.</typeparam>
template<typename array_type, template<typename, typename_array_size_type> class functor_template>
struct apply {
private:
    /// <summary>
    /// Helper for applying the function to each element in the array.
    /// </summary>
    /// <typeparam name="helper_array_type">The array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_functor_template">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<typename helper_array_type, template<typename, typename_array_size_type> class helper_functor_template, typename_array_size_type index>
    struct apply_helper;

    /// <summary>
    /// Helper specialization for an empty array.
    /// Notice that array_template uses typename... as a typename list. This is due to the fact that MSVC and GCC deduce template arguments differently.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="helper_functor_template">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<template<typename...> class array_template, template<typename, typename_array_size_type> class helper_functor_template, typename_array_size_type index>
    struct apply_helper<array_template<>, helper_functor_template, index> {
        /// <summary>
        /// The resulting array when the input is empty.
        /// </summary>
        using new_array = typename_array<>;
    };

    /// <summary>
    /// Specialization for processing the last element in the array.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The type of the last element.</typeparam>
    /// <typeparam name="helper_functor_template">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<template<typename...> class array_template, typename value_type, template<typename, typename_array_size_type> class helper_functor_template, typename_array_size_type index>
    struct apply_helper<array_template<value_type>, helper_functor_template, index> {
        /// <summary>
        /// The resulting array with a single transformed type.
        /// </summary>
        using new_array = typename_array<typename helper_functor_template<value_type, index>::new_value>;
    };

    /// <summary>
    /// Specialization for processing an array with multiple elements.
    /// Recursively applies the function to each element and combines the results.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="other_type">The remaining types in the array.</typeparam>
    /// <typeparam name="value_type">The current type being processed.</typeparam>
    /// <typeparam name="helper_functor_template">The transformation function template.</typeparam>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    template<template<typename...> class array_template, typename... other_type, typename value_type, template<typename, typename_array_size_type> class helper_functor_template, typename_array_size_type index>
    struct apply_helper<array_template<value_type, other_type...>, helper_functor_template, index> {
        /// <summary>
        /// The array resulting from combining the transformed current element with
        /// recursively processed remaining elements.
        /// </summary>
        using new_array = typename combine<
            typename_array<typename helper_functor_template<value_type, index>::new_value>,
            typename apply_helper<array_template<other_type...>, helper_functor_template, (index + 1)>::new_array
        >::new_array;
    };

public:
    /// <summary>
    /// The resulting array after applying the function to each element of the input array.
    /// </summary>
    using new_array = typename apply_helper<array_type, functor_template, 0>::new_array;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_APPLY_H