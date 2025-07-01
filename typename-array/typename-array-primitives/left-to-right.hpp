#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_LEFT_TO_RIGHT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_LEFT_TO_RIGHT_H

#include "base.hpp"

/// <summary>
/// Reverses the order of types in a typename_array, from left to right.
/// </summary>
/// <typeparam name="array_type">The typename array to reverse.</typeparam>
template<typename array_type>
struct left_to_right {
private:
    /// <summary>
    /// Base helper structure for reversing the order of types.
    /// Provides the final reversed array when recursion is complete.
    /// </summary>
    /// <typeparam name="counter">Position counter for tracking progress through the array.</typeparam>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    template<typename_array_size_type counter, typename helper_array_type>
    struct left_to_right_helper {
        /// <summary>
        /// The resulting array after reversal operations.
        /// </summary>
        using new_array = helper_array_type;
    };

    /// <summary>
    /// Specialization that processes each type in the array from left to right,
    /// building a new array with reversed order.
    /// </summary>
    /// <typeparam name="counter">Position counter for tracking progress through the array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="value_type">Current type being processed.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    template<typename_array_size_type counter, template<typename...> class array_template, typename value_type, typename... other_types>
    struct left_to_right_helper<counter, array_template<value_type, other_types...>> {
        /// <summary>
        /// Recursively builds the reversed array by combining the result of
        /// processing remaining types with the current type.
        /// </summary>
        using new_array = typename combine<
            typename left_to_right_helper<counter - 1, typename_array<other_types...>>::new_array,
            typename_array<value_type>
        >::new_array;
    };

public:
    /// <summary>
    /// The resulting array with types in reversed order.
    /// </summary>
    using new_array = typename left_to_right_helper<array_type::size, array_type>::new_array;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_LEFT_TO_RIGHT_H