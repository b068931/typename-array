#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_H

#include "base.hpp"

/// <summary>
/// Replaces a type at a specific index in a typename array with a new type.
/// </summary>
/// <typeparam name="replace_index">The index where the type will be replaced.</typeparam>
/// <typeparam name="array_type">The source typename array.</typeparam>
/// <typeparam name="new_type">The new type that will replace the existing one.</typeparam>
template<typename_array_size_type replace_index, typename array_type, typename new_type>
struct replace {
private:
    /// <summary>
    /// Forward declaration of the helper structure for replacing types in the array.
    /// </summary>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    /// <typeparam name="helper_array_type">The array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_new_type">The new type to insert at the target position.</typeparam>
    template<typename_array_size_type index, typename helper_array_type, typename helper_new_type>
    struct replace_helper;

    /// <summary>
    /// Specialization for when the current position matches the target replacement index.
    /// Replaces the first type with the new type and maintains the rest of the types.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The original type being replaced.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    /// <typeparam name="helper_new_type">The new type to replace with.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types, typename helper_new_type>
    struct replace_helper<replace_index, array_template<value_type, other_types...>, helper_new_type> {
        /// <summary>
        /// The resulting array after replacement, with the new type at the target position.
        /// </summary>
        using new_array = array_template<helper_new_type, other_types...>;
    };

    /// <summary>
    /// Specialization for when the current position doesn't match the target replacement index.
    /// Keeps the current type and continues recursion for the rest of the array.
    /// </summary>
    /// <typeparam name="index">Current position in the array being processed.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The current type to keep.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    /// <typeparam name="helper_new_type">The new type to insert at the target position.</typeparam>
    template<typename_array_size_type index, template<typename...> class array_template, typename value_type, typename... other_types, typename helper_new_type>
    struct replace_helper<index, array_template<value_type, other_types...>, helper_new_type> {
        /// <summary>
        /// The resulting array from keeping the current type and processing the rest of the array.
        /// Uses combine to prepend the current type to the array resulting from the recursive call.
        /// </summary>
        using new_array = typename combine<typename_array<value_type>, typename replace_helper<index + 1, array_template<other_types...>, helper_new_type>::new_array>::new_array;
    };

public:
    static_assert(replace_index < array_type::size, "Replace index must be less than the size of the array.");
    static_assert(replace_index >= 0, "Replace index must be non-negative.");

    /// <summary>
    /// The resulting array after replacing the type at the specified index.
    /// </summary>
    using new_array = typename replace_helper<0, array_type, new_type>::new_array;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_H