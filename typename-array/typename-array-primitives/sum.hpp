#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SUM_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SUM_H

#include "base.hpp"

/// <summary>
/// Calculates the sum of values associated with each type in a typename_array by applying a functor.
/// </summary>
/// <typeparam name="array_type">The typename array containing the types to process.</typeparam>
/// <typeparam name="functor_template">The functor template that extracts a value from each type.</typeparam>
/// <typeparam name="return_type">The type of the summed result.</typeparam>
template<typename array_type, template<typename> class functor_template, typename return_type>
struct sum {
private:
    /// <summary>
    /// Base helper structure for summing values.
    /// Provides the final sum when recursion is complete.
    /// </summary>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_functor_template">The functor template applied to each type.</typeparam>
    template<typename helper_array_type, template<typename> class helper_functor_template>
    struct sum_helper {
        /// <summary>
        /// The value for an empty array (base case).
        /// </summary>
        static constexpr return_type new_value{ 0 };
    };

    /// <summary>
    /// Specialization for when the array contains a single type.
    /// Extracts the value from that type using the functor.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The single type in the array.</typeparam>
    /// <typeparam name="helper_functor_template">The functor template applied to the type.</typeparam>
    template<template<typename> class array_template, typename value_type, template<typename> class helper_functor_template>
    struct sum_helper<array_template<value_type>, helper_functor_template> {
        /// <summary>
        /// The value extracted from the single type.
        /// </summary>
        static constexpr return_type new_value = helper_functor_template<value_type>::value;
    };

    /// <summary>
    /// Specialization for when the array contains multiple types.
    /// Applies the functor to the first type and recursively processes the rest.
    /// </summary>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">The current type being processed.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    /// <typeparam name="helper_functor_template">The functor template applied to each type.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename... other_types, template<typename> class helper_functor_template>
    struct sum_helper<array_template<value_type, other_types...>, helper_functor_template> {
        /// <summary>
        /// The sum of the value from the current type plus the sum of values from remaining types.
        /// </summary>
        static constexpr decltype(auto) new_value = helper_functor_template<value_type>::value + sum_helper<array_template<other_types...>, helper_functor_template>::new_value;
    };

public:
    /// <summary>
    /// The total sum of values extracted from all types in the array.
    /// </summary>
    static constexpr decltype(auto) new_value = sum_helper<array_type, functor_template>::new_value;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SUM_H