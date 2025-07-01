#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_H

#include "base.hpp"

/// <summary>
/// Searches for a specific type in a typename array and provides its index.
/// </summary>
/// <typeparam name="array_type">The typename array to search within.</typeparam>
/// <typeparam name="helper_type_to_find">The type to find in the array.</typeparam>
template<typename array_type, typename type_to_find>
struct find {
private:
    /// <summary>
    /// Base helper structure for finding a type.
    /// Default case when the type is not found - returns npos.
    /// </summary>
    /// <typeparam name="helper_array_type">The array or remaining portion being searched.</typeparam>
    /// <typeparam name="helper_type_to_find">The type to find.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<typename helper_array_type, typename helper_type_to_find, typename_array_size_type index>
    struct find_helper {
        /// <summary>
        /// When no match is found, returns npos (-1).
        /// </summary>
        static constexpr typename_array_size_type indx = npos;
    };

    /// <summary>
    /// Specialization for when the current type doesn't match the target.
    /// Continues the search in the rest of the array.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type (non-matching).</typeparam>
    /// <typeparam name="other_type">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_type_to_find">The type to find.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_type, typename helper_type_to_find, typename_array_size_type index>
    struct find_helper<array_template<value_type, other_type...>, helper_type_to_find, index> {
        /// <summary>
        /// Recursively search in the remaining types, incrementing the index.
        /// </summary>
        static constexpr typename_array_size_type indx = find_helper<array_template<other_type...>, helper_type_to_find, index + 1>::indx;
    };

    /// <summary>
    /// Specialization for when the current type matches the target.
    /// Terminates the search and returns the current index.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="other_type">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_type_to_find">The matching type found.</typeparam>
    /// <typeparam name="index">Current position in the search (result).</typeparam>
    template<template<typename...> class array_template, typename... other_type, typename helper_type_to_find, typename_array_size_type index>
    struct find_helper<array_template<helper_type_to_find, other_type...>, helper_type_to_find, index> {
        /// <summary>
        /// Returns the current index as the match is found.
        /// </summary>
        static constexpr typename_array_size_type indx = index;
    };

public:
    /// <summary>
    /// The index of the first occurrence of type_to_find in the array,
    /// or npos (-1) if the type is not present.
    /// </summary>
    static constexpr typename_array_size_type index = find_helper<array_type, type_to_find, 0>::indx;
};


#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_H