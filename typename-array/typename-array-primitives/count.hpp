#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_COUNT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_COUNT_H

#include "base.hpp"

/// <summary>
/// Counts occurrences of a specific type within a typename_array.
/// </summary>
/// <typeparam name="array_type">The typename array to search within.</typeparam>
/// <typeparam name="type_to_count">The type to count occurrences of.</typeparam>
template<typename array_type, typename type_to_count>
struct count {
private:
    /// <summary>
    /// Base helper structure for counting type occurrences.
    /// Provides the final count when recursion is complete.
    /// </summary>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_type_to_count">The type being counted.</typeparam>
    /// <typeparam name="appearances_counter">Running count of occurrences found so far.</typeparam>
    template<typename helper_array_type, typename helper_type_to_count, typename_array_size_type appearances_counter>
    struct count_helper {
        /// <summary>
        /// The accumulated count of matching types.
        /// </summary>
        static constexpr typename_array_size_type counter = appearances_counter;
    };

    /// <summary>
    /// Specialization for when the current type doesn't match the target type.
    /// Continues recursion without incrementing the counter.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type being examined (non-matching).</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_type_to_count">The type being counted.</typeparam>
    /// <typeparam name="appearances_counter">Running count of occurrences found so far.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types, typename helper_type_to_count, typename_array_size_type appearances_counter>
    struct count_helper<array_template<value_type, other_types...>, helper_type_to_count, appearances_counter> {
        /// <summary>
        /// Continues counting in the rest of the array without incrementing.
        /// </summary>
        static constexpr typename_array_size_type counter = count_helper<
            array_template<other_types...>,
            helper_type_to_count,
            appearances_counter
        >::counter;
    };

    /// <summary>
    /// Specialization for when the current type matches the target type.
    /// Increments the counter and continues recursion.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_type_to_count">The type being counted (matched).</typeparam>
    /// <typeparam name="appearances_counter">Running count of occurrences found so far.</typeparam>
    template<template<typename...> class array_template, typename... other_types, typename helper_types_to_count, typename_array_size_type appearances_counter>
    struct count_helper<array_template<helper_types_to_count, other_types...>, helper_types_to_count, appearances_counter> {
        /// <summary>
        /// Continues counting in the rest of the array after incrementing the counter.
        /// </summary>
        static constexpr typename_array_size_type counter = count_helper<
            array_template<other_types...>,
            helper_types_to_count,
            appearances_counter + 1
        >::counter;
    };

public:
    /// <summary>
    /// The total number of occurrences of the specified type in the array.
    /// </summary>
    static constexpr typename_array_size_type counter = count_helper<array_type, type_to_count, 0>::counter;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_COUNT_H