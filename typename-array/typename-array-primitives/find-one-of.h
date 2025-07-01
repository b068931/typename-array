#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_ONE_OF_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_ONE_OF_H

#include "base.h"
#include "find.h"

/// <summary>
/// Finds the first occurrence of any type from one array within another array.
/// </summary>
/// <typeparam name="array_type">The typename array to search within.</typeparam>
/// <typeparam name="array_to_find_type">The array of types to search for.</typeparam>
template<typename array_type, typename array_to_find_type>
struct find_one_of {
private:
    /// <summary>
    /// Base helper structure for finding any type from one array in another.
    /// Returns npos when no match is found.
    /// </summary>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_array_to_find_type">The array of types to search for.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    /// <typeparam name="is_found">Flag indicating if a match has been found.</typeparam>
    template<typename helper_array_type, typename helper_array_to_find_type, typename_array_size_type index, bool is_found>
    struct find_one_of_helper {
        /// <summary>
        /// Default case: no match found, return npos.
        /// </summary>
        static constexpr typename_array_size_type indx = npos;
    };

    /// <summary>
    /// Specialization for when a match hasn't been found yet.
    /// Continues recursion, checking if the current type exists in the array_to_find.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type being examined.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_array_to_find_type">The array of types to search for.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types, typename helper_array_to_find_type, typename_array_size_type index>
    struct find_one_of_helper<array_template<value_type, other_types...>, helper_array_to_find_type, index, false> {
        /// <summary>
        /// Continues searching, using find to check if val exists in helper_array_to_find.
        /// </summary>
        static constexpr typename_array_size_type indx = find_one_of_helper<array_template<other_types...>, helper_array_to_find_type, index + 1, (find<helper_array_to_find_type, value_type>::index != -1)>::indx;
    };

    /// <summary>
    /// Specialization for when a match has been found.
    /// Stops recursion and returns the current index.
    /// </summary>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_array_to_find_type">The array of types to search for.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<typename helper_array_type, typename helper_array_to_find_type, typename_array_size_type index>
    struct find_one_of_helper<helper_array_type, helper_array_to_find_type, index, true> {
        /// <summary>
        /// Match found, return the current index.
        /// </summary>
        static constexpr typename_array_size_type indx = index;
    };

public:
    /// <summary>
    /// The index of the first occurrence of any type from array_to_find in array,
    /// or npos if none are found.
    /// </summary>
    static constexpr typename_array_size_type index = find_one_of_helper<array_type, array_to_find_type, -1, false>::indx;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_ONE_OF_H