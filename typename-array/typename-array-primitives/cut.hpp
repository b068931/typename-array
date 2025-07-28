#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CUT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CUT_H

#include "base.hpp"

/// <summary>
/// Extracts a subset of types from a typename array based on specified indices.
/// </summary>
/// <typeparam name="start_index">The starting index (inclusive) of the range to extract.</typeparam>
/// <typeparam name="end_index">The ending index (inclusive) of the range to extract.</typeparam>
/// <typeparam name="array_type">The source typename array to extract types from.</typeparam>
template<typename_array_size_type start_index, typename_array_size_type end_index, typename array_type>
struct cut {
private:
    /// <summary>
    /// Base helper template for cutting arrays.
    /// </summary>
    /// <typeparam name="use">Whether the current element should be included.</typeparam>
    /// <typeparam name="index">Current position in the source array.</typeparam>
    /// <typeparam name="helper_array_type">Type holding the remaining elements to process.</typeparam>
    template<bool use, typename_array_size_type index, typename helper_array_type>
    struct cut_helper {
        /// <summary>
        /// Empty result for base case or when no elements match the criteria.
        /// </summary>
        using new_array = typename_array<>;
    };

    /// <summary>
    /// Specialization for processing elements that are outside the requested range.
    /// Skips the current element and continues recursively.
    /// </summary>
    /// <typeparam name="use">Whether the current element should be included (false in this case).</typeparam>
    /// <typeparam name="index">Current position in the source array.</typeparam>
    /// <typeparam name="value_type">The current type being processed.</typeparam>
    /// <typeparam name="other_types">The remaining types in the source array.</typeparam>
    /// <typeparam name="array_template">The template class of the source array.</typeparam>
    template<bool use, typename_array_size_type index, typename value_type, typename... other_types, template<typename...> class array_template>
    struct cut_helper<use, index, array_template<value_type, other_types...>> {
        static constexpr typename_array_size_type next_index = index + 1;
        using new_array = typename cut_helper<
            next_index >= start_index && next_index <= end_index,
             next_index,
            array_template<other_types...>
        >::new_array;
    };

    /// <summary>
    /// Specialization for processing elements that are within the requested range.
    /// Includes the current element and continues recursively.
    /// </summary>
    /// <typeparam name="index">Current position in the source array.</typeparam>
    /// <typeparam name="value_type">The current type being processed.</typeparam>
    /// <typeparam name="other_types">The remaining types in the source array.</typeparam>
    /// <typeparam name="array_template">The template class of the source array.</typeparam>
    template<typename_array_size_type index, typename value_type, typename... other_types, template<typename...> class array_template>
    struct cut_helper<true, index, array_template<value_type, other_types...>> {
        static constexpr typename_array_size_type next_index = index + 1;
        using new_array = typename combine<
            array_template<value_type>,
            typename cut_helper<
                next_index >= start_index && next_index <= end_index,
                next_index,
                array_template<other_types...>
            >::new_array
        >::new_array;
    };

public:
    /// <summary>
    /// The resulting array containing only the types from the specified index range.
    /// Returns an empty array if start/end indices are invalid (if start > end, 
    /// start is negative, or end is beyond array bounds).
    /// </summary>
    using new_array = typename cut_helper<start_index == 0 && end_index >= start_index && end_index < array_type::size, 0, array_type>::new_array;
    static_assert(start_index >= 0, "Invalid start index: must be non-negative.");
    static_assert(end_index < array_type::size, "Invalid end index: must be within array bounds.");
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_CUT_H