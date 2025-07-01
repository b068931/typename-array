#ifndef TYPENAME_ARRAY_TYPENAME_PRIMITIVES_ERASE_H
#define TYPENAME_ARRAY_TYPENAME_PRIMITIVES_ERASE_H

#include "base.hpp"

/// <summary>
/// Removes a type at the specified index from a typename array.
/// </summary>
/// <typeparam name="index_to_erase">The zero-based index of the type to remove.</typeparam>
/// <typeparam name="array_type">The typename array to remove the type from.</typeparam>
template<typename_array_size_type index_to_erase, typename array_type>
struct erase {
public:
    /// <summary>
    /// Helper template for implementation of type erasure at specific index.
    /// </summary>
    /// <typeparam name="index">Current index being processed during recursion.</typeparam>
    /// <typeparam name="helper_array_type">The array being processed.</typeparam>
    template<typename_array_size_type index, typename helper_array_type>
    struct erase_helper;

    /// <summary>
    /// Specialization for when the current index matches the index to erase.
    /// Skips the current type and keeps only the remaining types.
    /// </summary>
    /// <typeparam name="array_template">The template for the array container.</typeparam>
    /// <typeparam name="value_type">The type at the index to be erased.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types>
    struct erase_helper<index_to_erase, array_template<value_type, other_types...>> {
        /// <summary>
        /// The resulting array after removing the type at the specified index.
        /// </summary>
        using new_array = typename_array<other_types...>;
    };

    /// <summary>
    /// Specialization for when the current index doesn't match the index to erase.
    /// Keeps the current type and continues processing the rest of the array.
    /// </summary>
    /// <typeparam name="index">Current index being processed during recursion.</typeparam>
    /// <typeparam name="array_template">The template for the array container.</typeparam>
    /// <typeparam name="value_type">The type at the current index.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    template<typename_array_size_type index, template<typename...> class array_template, typename value_type, typename... other_types>
    struct erase_helper<index, array_template<value_type, other_types...>> {
        /// <summary>
        /// The resulting array, combining the current type with the result of processing the rest.
        /// </summary>
        using new_array = typename combine<typename_array<value_type>, typename erase_helper<index + 1, typename_array<other_types...>>::new_array>::new_array;
    };

public:
    /// <summary>
    /// The final array type after erasing the specified type.
    /// </summary>
    using new_array = typename erase_helper<0, array_type>::new_array;
    static_assert(index_to_erase < array_type::size, "Index to erase is out of bounds for the array size.");
};

#endif // TYPENAME_ARRAY_TYPENAME_PRIMITIVES_ERASE_H