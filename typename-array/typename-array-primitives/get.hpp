#ifndef TYPENAME_ARRAY_GET_H
#define TYPENAME_ARRAY_GET_H

#include "base.hpp"

/// <summary>
/// Retrieves the type at a specific index within a typename_array.
/// </summary>
/// <typeparam name="index">The zero-based index of the element to retrieve.</typeparam>
/// <typeparam name="array_type">The typename array to retrieve from.</typeparam>
template<typename_array_size_type index, typename array_type>
struct get {
private:
    /// <summary>
    /// Helper structure for recursively accessing elements at a specific index.
    /// </summary>
    /// <typeparam name="counter">Current recursion depth/index position.</typeparam>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    template<typename_array_size_type counter, typename helper_array_type>
    struct get_helper;

    /// <summary>
    /// Specialization for when the counter reaches zero (target index found).
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The type at the target index position.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array (not used in this specialization).</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types>
    struct get_helper<0, array_template<value_type, other_types...>> {
        /// <summary>
        /// The type at the target index.
        /// </summary>
        using value = value_type;
    };

    /// <summary>
    /// Specialization for recursive traversal when counter is greater than zero.
    /// </summary>
    /// <typeparam name="counter">Remaining steps to reach target index.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type being examined (skipped).</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    template<typename_array_size_type counter, template<typename...> class array_template, typename value_type, typename... other_types>
    struct get_helper<counter, array_template<value_type, other_types...>> {
        /// <summary>
        /// Recursively access the next element by decrementing the counter.
        /// </summary>
        using value = typename get_helper<counter - 1, typename_array<other_types...>>::value;
    };

public:
    static_assert(index < array_type::size, "Index out of bounds in typename_array::get.");
    static_assert(index >= 0, "Index must be greater than or equal to 0 in typename_array::get.");
    
    /// <summary>
    /// The type at the specified index position in the array.
    /// </summary>
    using value = typename get_helper<index, array_type>::value;
};

#endif // TYPENAME_ARRAY_GET_H