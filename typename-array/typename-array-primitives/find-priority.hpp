#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_PRIORITY_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_PRIORITY_H

#include "base.hpp"
#include "find.hpp"
#include "value-wrapper.hpp"

/// <summary>
/// Finds the first type from array_to_find that exists in the array, returning its index.
/// </summary>
/// <typeparam name="array_type">The typename array to search within.</typeparam>
/// <typeparam name="array_to_find_type">Array of types to search for in priority order.</typeparam>
template<typename array_type, typename array_to_find_type>
struct find_priority {
private:
    /// <summary>
    /// Base helper structure for priority search implementation.
    /// Returns npos when no matching types are found.
    /// </summary>
    /// <typeparam name="helper_array_type">Array being searched.</typeparam>
    /// <typeparam name="helper_array_to_find_type">Remaining types to search for.</typeparam>
    template<typename helper_array_type, typename helper_array_to_find_type>
    struct find_priority_helper {
        /// <summary>
        /// Default result when no match is found.
        /// </summary>
        static constexpr typename_array_size_type get_value = npos;
    };

    /// <summary>
    /// Specialization that recursively searches for types in priority order.
    /// Attempts to find the first type (value_type), falling back to the next type if not found.
    /// </summary>
    /// <typeparam name="array_template">The template of the array_to_find.</typeparam>
    /// <typeparam name="value_type">Current type to search for.</typeparam>
    /// <typeparam name="other_types">Remaining types to search for if current type not found.</typeparam>
    /// <typeparam name="helper_array_type">The array being searched.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types, typename helper_array_type>
    struct find_priority_helper<helper_array_type, array_template<value_type, other_types...>> {
        /// <summary>
        /// Determines whether to continue with the current match or try the next type.
        /// </summary>
        using trailing_result = std::conditional_t<
            find<helper_array_type, value_type>::index == -1,
            find_priority_helper<helper_array_type, array_template<other_types...>>,
            value_wrapper<find<helper_array_type, value_type>::index>
        >;

        /// <summary>
        /// The index of the first matching type found, or npos if none found.
        /// Notice that "get_value" is used everywhere, this is due to the fact that it needs to be compatible with value_wrapper.
        /// </summary>
        static constexpr typename_array_size_type get_value = trailing_result::get_value;
    };

public:
    /// <summary>
    /// The index of the first type from array_to_find found in array, or npos if none found.
    /// Types are checked in the order they appear in array_to_find.
    /// </summary>
    static constexpr typename_array_size_type index = find_priority_helper<array_type, array_to_find_type>::get_value;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_PRIORITY_H