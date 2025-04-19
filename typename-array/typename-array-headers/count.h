#ifndef TYPENAME_ARRAY_COUNT_H
#define TYPENAME_ARRAY_COUNT_H

#include "base.h"

/// <summary>
/// Counts occurrences of a specific type within a typename_array.
/// </summary>
/// <typeparam name="array">The typename array to search within.</typeparam>
/// <typeparam name="value_to_count">The type to count occurrences of.</typeparam>
template<typename array, typename value_to_count>
struct count {
private:
    /// <summary>
    /// Base helper structure for counting type occurrences.
    /// Provides the final count when recursion is complete.
    /// </summary>
    /// <typeparam name="helper_array">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_value_to_count">The type being counted.</typeparam>
    /// <typeparam name="appearances">Running count of occurrences found so far.</typeparam>
    template<typename helper_array, typename helper_value_to_count, typename_array_size_t appearances>
    struct count_helper {
        /// <summary>
        /// The accumulated count of matching types.
        /// </summary>
        static constexpr typename_array_size_t counter = appearances;
    };

    /// <summary>
    /// Specialization for when the current type doesn't match the target type.
    /// Continues recursion without incrementing the counter.
    /// </summary>
    /// <typeparam name="templ">The template of the array.</typeparam>
    /// <typeparam name="value">Current type being examined (non-matching).</typeparam>
    /// <typeparam name="other">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_value_to_count">The type being counted.</typeparam>
    /// <typeparam name="appearances">Running count of occurrences found so far.</typeparam>
    template<template<typename, typename...> class templ, typename value, typename... other, typename helper_value_to_count, typename_array_size_t appearances>
    struct count_helper<templ<value, other...>, helper_value_to_count, appearances> {
        /// <summary>
        /// Continues counting in the rest of the array without incrementing.
        /// </summary>
        static constexpr typename_array_size_t counter = count_helper<templ<other...>, helper_value_to_count, appearances>::counter;
    };

    /// <summary>
    /// Specialization for when the current type matches the target type.
    /// Increments the counter and continues recursion.
    /// </summary>
    /// <typeparam name="templ">The template of the array.</typeparam>
    /// <typeparam name="other">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_value_to_count">The type being counted (matched).</typeparam>
    /// <typeparam name="appearances">Running count of occurrences found so far.</typeparam>
    template<template<typename, typename...> class templ, typename... other, typename helper_value_to_count, typename_array_size_t appearances>
    struct count_helper<templ<helper_value_to_count, other...>, helper_value_to_count, appearances> {
        /// <summary>
        /// Continues counting in the rest of the array after incrementing the counter.
        /// </summary>
        static constexpr typename_array_size_t counter = count_helper<templ<other...>, helper_value_to_count, (appearances + 1)>::counter;
    };

public:
    /// <summary>
    /// The total number of occurrences of the specified type in the array.
    /// </summary>
    static constexpr typename_array_size_t counter = count_helper<array, value_to_count, 0>::counter;
};

#endif // TYPENAME_ARRAY_COUNT_H