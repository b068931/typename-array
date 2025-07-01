#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SORT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SORT_H

#include "base.hpp"
#include "get.hpp"
#include "cut.hpp"

/// <summary>
/// Sorts a typename array according to a specified predicate.
/// </summary>
/// <typeparam name="array_type">The typename array to be sorted.</typeparam>
/// <typeparam name="predicate_template">Binary predicate template that determines sort order. Returns true if first type ordered before second.</typeparam>
template<typename array_type, template<typename, typename> class predicate_template>
struct sort {
private:
    /// <summary>
    /// Helper structure to merge two sorted arrays into a single sorted array.
    /// </summary>
    /// <typeparam name="first_array_type">The first sorted array.</typeparam>
    /// <typeparam name="second_array_type">The second sorted array.</typeparam>
    template<typename first_array_type, typename second_array_type>
    struct combine_sorted_arrays;

    /// <summary>
    /// Specialization for when the second array is empty or invalid.
    /// </summary>
    /// <typeparam name="other_type">The type of the second (empty) array.</typeparam>
    /// <typeparam name="first_value_type">The first type in the first array.</typeparam>
    /// <typeparam name="first_other_types">Remaining types in the first array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename other_type, typename first_value_type, typename... first_other_types, template<typename...> class array_template>
    struct combine_sorted_arrays<array_template<first_value_type, first_other_types...>, other_type> {
        /// <summary>
        /// Returns the first array unchanged when the second array is empty.
        /// </summary>
        using new_array = array_template<first_value_type, first_other_types...>;
    };

    /// <summary>
    /// Specialization for when the first array is empty or invalid.
    /// </summary>
    /// <typeparam name="other_type">The type of the first (empty) array.</typeparam>
    /// <typeparam name="second_value_type">The first type in the second array.</typeparam>
    /// <typeparam name="second_other_types">Remaining types in the second array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename other_type, typename second_value_type, typename... second_other_types, template<typename...> class array_template>
    struct combine_sorted_arrays<other_type, array_template<second_value_type, second_other_types...>> {
        /// <summary>
        /// Returns the second array unchanged when the first array is empty.
        /// </summary>
        using new_array = array_template<second_value_type, second_other_types...>;
    };

    /// <summary>
    /// Specialization for combining two non-empty arrays by comparing their first elements.
    /// </summary>
    /// <typeparam name="first_value_type">The first type in the first array.</typeparam>
    /// <typeparam name="first_other_types">Remaining types in the first array.</typeparam>
    /// <typeparam name="second_value_type">The first type in the second array.</typeparam>
    /// <typeparam name="second_other_types">Remaining types in the second array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename first_value_type, typename... first_other_types, typename second_value_type, typename... second_other_types, template<typename...> class array_template>
    struct combine_sorted_arrays<array_template<first_value_type, first_other_types...>, array_template<second_value_type, second_other_types...>> {
        /// <summary>
        /// Determines if the first value should come before the second value according to the predicate.
        /// </summary>
        static constexpr bool is_value_before = predicate_template<first_value_type, second_value_type>::value;

        /// <summary>
        /// The type to be placed at the front of the merged array.
        /// </summary>
        using first_val = std::conditional_t<is_value_before, first_value_type, second_value_type>;
        
        /// <summary>
        /// The remaining arrays to be merged after removing the selected first element.
        /// </summary>
        using arrays = std::conditional_t<
            is_value_before,
            array_template<array_template<first_other_types...>, array_template<second_value_type, second_other_types...>>,
            array_template<array_template<first_value_type, first_other_types...>, array_template<second_other_types...>>
        >;

        /// <summary>
        /// The merged array combining the selected first element with the recursively merged remainder.
        /// </summary>
        using new_array = typename combine<array_template<first_val>,
            typename combine_sorted_arrays<typename get<0, arrays>::value,
            typename get<1, arrays>::value>::new_array
        >::new_array;
    };

    /// <summary>
    /// Base helper structure for sorting arrays using merge sort algorithm.
    /// </summary>
    /// <typeparam name="first_type">First portion of the array to sort.</typeparam>
    /// <typeparam name="second_type">Second portion of the array to sort.</typeparam>
    template<typename first_type, typename second_type>
    struct sort_help {
        /// <summary>
        /// Default case returns an empty array.
        /// </summary>
        using new_array = typename_array<>;
    };

    /// <summary>
    /// Specialization for when the first portion is empty.
    /// </summary>
    /// <typeparam name="first_type">Empty or invalid first portion.</typeparam>
    /// <typeparam name="value_type">First type in the second portion.</typeparam>
    /// <typeparam name="other_types">Remaining types in the second portion.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename first_type, typename value_type, typename... other_types, template<typename...> class array_template>
    struct sort_help<first_type, array_template<value_type, other_types...>> {
        /// <summary>
        /// Returns the second portion unchanged when the first portion is empty.
        /// </summary>
        using new_array = array_template<value_type, other_types...>;
    };

    /// <summary>
    /// Specialization for when the second portion is empty.
    /// </summary>
    /// <typeparam name="second_type">Empty or invalid second portion.</typeparam>
    /// <typeparam name="value_type">First type in the first portion.</typeparam>
    /// <typeparam name="other_types">Remaining types in the first portion.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename second_type, typename value_type, typename... other_types, template<typename...> class array_template>
    struct sort_help<array_template<value_type, other_types...>, second_type> {
        /// <summary>
        /// Returns the first portion unchanged when the second portion is empty.
        /// </summary>
        using new_array = array_template<value_type, other_types...>;
    };

    /// <summary>
    /// Specialization for sorting two single-element arrays.
    /// </summary>
    /// <typeparam name="first_other_type">The type in the first array.</typeparam>
    /// <typeparam name="second_other_type">The type in the second array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename first_other_type, typename second_other_type, template<typename> class array_template>
    struct sort_help<array_template<first_other_type>, array_template<second_other_type>> {
        /// <summary>
        /// The first single-element array.
        /// </summary>
        using first_array_type = array_template<first_other_type>;
        
        /// <summary>
        /// The second single-element array.
        /// </summary>
        using second_array_type = array_template<second_other_type>;

        /// <summary>
        /// Merges the two single-element arrays in sorted order.
        /// </summary>
        using new_array = typename combine_sorted_arrays<first_array_type, second_array_type>::new_array;
    };

    /// <summary>
    /// Specialization for sorting two multi-element arrays using divide-and-conquer approach.
    /// </summary>
    /// <typeparam name="first_value_type">First type in the first array.</typeparam>
    /// <typeparam name="second_value_type">First type in the second array.</typeparam>
    /// <typeparam name="first_other_types">Remaining types in the first array.</typeparam>
    /// <typeparam name="second_other_types">Remaining types in the second array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    template<typename first_value_type, typename second_value_type, typename... first_other_types, typename... second_other_types, template<typename...> class array_template>
    struct sort_help<array_template<first_value_type, first_other_types...>, array_template<second_value_type, second_other_types...>> {
        /// <summary>
        /// The first array to be sorted.
        /// </summary>
        using first_array_type = array_template<first_value_type, first_other_types...>;
        
        /// <summary>
        /// The second array to be sorted.
        /// </summary>
        using second_array_type = array_template<second_value_type, second_other_types...>;

        /// <summary>
        /// Midpoint index of the first array.
        /// </summary>
        static constexpr typename_array_size_type first = first_array_type::size / 2;
        
        /// <summary>
        /// Midpoint index of the second array.
        /// </summary>
        static constexpr typename_array_size_type second = second_array_type::size / 2;

        /// <summary>
        /// Recursively sorts the first array by dividing it and merging the sorted halves.
        /// </summary>
        using first_half = typename sort_help<
            typename cut<0, first - 1, first_array_type>::new_array,
            typename cut<first, first_array_type::size - 1, first_array_type>::new_array
        >::new_array;

        /// <summary>
        /// Recursively sorts the second array by dividing it and merging the sorted halves.
        /// </summary>
        using second_half = typename sort_help<
            typename cut<0, second - 1, second_array_type>::new_array,
            typename cut<second, second_array_type::size - 1, second_array_type>::new_array
        >::new_array;

        /// <summary>
        /// Merges the two sorted arrays to produce the final sorted result.
        /// </summary>
        using new_array = typename combine_sorted_arrays<first_half, second_half>::new_array;
    };

    /// <summary>
    /// Midpoint index of the input array.
    /// </summary>
    static constexpr typename_array_size_type half = array_type::size / 2;

public:
    /// <summary>
    /// The sorted array produced by applying merge sort to the input array.
    /// </summary>
    using new_array = typename sort_help<
        typename cut<0, half - 1, array_type>::new_array,
        typename cut<half, array_type::size - 1, array_type>::new_array
    >::new_array;
};


#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SORT_H