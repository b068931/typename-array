#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CHECK_FOR_ALLOWED_TYPES_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CHECK_FOR_ALLOWED_TYPES_H

#include "base.h"
#include "find.h"

/// <summary>
/// Verifies that all types in the array are present in the allowed_types list.
/// </summary>
/// <typeparam name="array_type">The array_type of types to validate.</typeparam>
/// <typeparam name="allowed_types">The array of permitted types.</typeparam>
template<typename array_type, typename allowed_types>
struct check_for_allowed_types {
private:
    /// <summary>
    /// Base helper structure for validation with termination condition.
    /// Default specialization that indicates validation failure.
    /// </summary>
    /// <typeparam name="helper_array_type">Array being validated.</typeparam>
    /// <typeparam name="helper_allowed_types">Array of allowed types.</typeparam>
    /// <typeparam name="is_continue">Flag to continue validation or terminate with failure.</typeparam>
    template<typename helper_array_type, typename helper_allowed_types, bool is_continue>
    struct check_for_allowed_types_helper {
        /// <summary>
        /// Indicates validation failure.
        /// </summary>
        static constexpr bool is_valid = false;
    };

    /// <summary>
    /// Specialization for empty array case - all validation is complete.
    /// </summary>
    /// <typeparam name="helper_array_type">Empty array (validation complete).</typeparam>
    /// <typeparam name="helper_allowed_types">Array of allowed types.</typeparam>
    template<typename helper_array_type, typename helper_allowed_types>
    struct check_for_allowed_types_helper<helper_array_type, helper_allowed_types, true> {
        /// <summary>
        /// Indicates successful validation (all types are allowed).
        /// </summary>
        static constexpr bool is_valid = true;
    };

    /// <summary>
    /// Specialization that recursively checks each type in the array.
    /// Continues validation only if the current type is found in the allowed types.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type being checked.</typeparam>
    /// <typeparam name="other_type">Remaining types to check.</typeparam>
    /// <typeparam name="helper_allowed_types">Array of allowed types.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_type, typename helper_allowed_types>
    struct check_for_allowed_types_helper<array_template<value_type, other_type...>, helper_allowed_types, true> {
        /// <summary>
        /// Recursively validates remaining types, continuing only if current type is allowed.
        /// Uses find to determine if the current type exists in the allowed_types array.
        /// </summary>
        static constexpr bool is_valid = check_for_allowed_types_helper<
            array_template<other_type...>, 
            helper_allowed_types, 
            (find<helper_allowed_types, value_type>::index != npos)
        >::is_valid;
    };

public:
    /// <summary>
    /// Result of validation. True if all types in the array are found
    /// in the allowed_types list, false otherwise.
    /// </summary>
    static constexpr bool is_valid = check_for_allowed_types_helper<array_type, allowed_types, true>::is_valid;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CHECK_FOR_ALLOWED_TYPES_H