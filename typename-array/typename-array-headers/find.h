#ifndef TYPENAME_ARRAY_FIND_H
#define TYPENAME_ARRAY_FIND_H

#include "base.h"

/// <summary>
/// Searches for a specific type in a typename array and provides its index.
/// </summary>
/// <typeparam name="array">The typename array to search within.</typeparam>
/// <typeparam name="val_to_find">The type to find in the array.</typeparam>
template<typename array, typename val_to_find>
struct find {
private:
    /// <summary>
    /// Base helper structure for finding a type.
    /// Default case when the type is not found - returns npos.
    /// </summary>
    /// <typeparam name="helper_array">The array or remaining portion being searched.</typeparam>
    /// <typeparam name="find">The type to find.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<typename helper_array, typename find, typename_array_size_t index>
    struct find_helper {
        /// <summary>
        /// When no match is found, returns npos (-1).
        /// </summary>
        static constexpr typename_array_size_t indx = npos;
    };

    /// <summary>
    /// Specialization for when the current type doesn't match the target.
    /// Continues the search in the rest of the array.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="val">Current type (non-matching).</typeparam>
    /// <typeparam name="other">Remaining types in the array.</typeparam>
    /// <typeparam name="find">The type to find.</typeparam>
    /// <typeparam name="index">Current position in the search.</typeparam>
    template<template<typename, typename...> class array_template, typename val, typename... other, typename find, typename_array_size_t index>
    struct find_helper<array_template<val, other...>, find, index> {
        /// <summary>
        /// Recursively search in the remaining types, incrementing the index.
        /// </summary>
        static constexpr typename_array_size_t indx = find_helper<array_template<other...>, find, index + 1>::indx;
    };

    /// <summary>
    /// Specialization for when the current type matches the target.
    /// Terminates the search and returns the current index.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="other">Remaining types in the array.</typeparam>
    /// <typeparam name="find">The matching type found.</typeparam>
    /// <typeparam name="index">Current position in the search (result).</typeparam>
    template<template<typename, typename...> class array_template, typename... other, typename find, typename_array_size_t index>
    struct find_helper<array_template<find, other...>, find, index> {
        /// <summary>
        /// Returns the current index as the match is found.
        /// </summary>
        static constexpr typename_array_size_t indx = index;
    };

public:
    /// <summary>
    /// The index of the first occurrence of val_to_find in the array,
    /// or npos (-1) if the type is not present.
    /// </summary>
    static constexpr typename_array_size_t index = find_helper<array, val_to_find, 0>::indx;
};


#endif // TYPENAME_ARRAY_FIND_H