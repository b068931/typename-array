#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_N_APPEARANCE_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_N_APPEARANCE_H

#include "base.hpp"

/// <summary>
/// Finds the index of the Nth appearance of a specific type in a typename array.
/// </summary>
/// <typeparam name="array_type">The typename array to search in.</typeparam>
/// <typeparam name="type_to_find">The type to find within the array.</typeparam>
/// <typeparam name="counter">The occurrence number to find (1 for first appearance, 2 for second, etc.).</typeparam>
template<typename array_type, typename type_to_find, typename_array_size_type counter>
struct find_n_appearance {
private:
    /// <summary>
    /// Base helper struct for the recursive search algorithm.
    /// Returns npos when the type is not found or count appearances don't exist.
    /// </summary>
    /// <typeparam name="helper_array_type">The array type being searched.</typeparam>
    /// <typeparam name="helper_type_to_find">The type being searched for.</typeparam>
    /// <typeparam name="helper_counter">The remaining occurrences to find.</typeparam>
    /// <typeparam name="index">The current position in the array.</typeparam>
    /// <typeparam name="dummy">Boolean flag to control template specialization selection.</typeparam>
    template<typename helper_array_type, typename helper_type_to_find, typename_array_size_type helper_counter, typename_array_size_type index, bool dummy>
    struct find_n_appearance_helper {
        static constexpr typename_array_size_type indx = npos;
    };

    /// <summary>
    /// Specialization for when the current type doesn't match the search type.
    /// Continues searching through the rest of the array.
    /// </summary>
    /// <typeparam name="array_template">The template class of the array.</typeparam>
    /// <typeparam name="value_type">The current type being examined (not matching the search type).</typeparam>
    /// <typeparam name="helper_type_to_find">The type being searched for.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    /// <typeparam name="helper_counter">The remaining occurrences to find.</typeparam>
    /// <typeparam name="index">The current position in the array.</typeparam>
    template<template<typename...> class array_template, typename value_type, typename helper_type_to_find, typename... other_types, typename_array_size_type helper_counter, typename_array_size_type index>
    struct find_n_appearance_helper<array_template<value_type, other_types...>, helper_type_to_find, helper_counter, index, true> {
        static constexpr typename_array_size_type indx = find_n_appearance_helper<
            array_template<other_types...>,
            helper_type_to_find,
            helper_counter,
            index + 1,
            true
        >::indx;
    };

    /// <summary>
    /// Specialization for when the current type matches the search type.
    /// Decrements the count and continues searching if more occurrences are needed.
    /// </summary>
    /// <typeparam name="array_template">The template class of the array.</typeparam>
    /// <typeparam name="helper_type_to_find">The type being searched for and currently matched.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array.</typeparam>
    /// <typeparam name="helper_counter">The remaining occurrences to find.</typeparam>
    /// <typeparam name="index">The current position in the array.</typeparam>
    template<template<typename...> class array_template, typename helper_type_to_find, typename... other_types, typename_array_size_type helper_counter, typename_array_size_type index>
    struct find_n_appearance_helper<array_template<helper_type_to_find, other_types...>, helper_type_to_find, helper_counter, index, true> {
        static constexpr typename_array_size_type indx = find_n_appearance_helper<
            array_template<other_types...>,
            helper_type_to_find,
            helper_counter - 1,
            index + 1,
            helper_counter - 1 != 0
        >::indx;
    };

    /// <summary>
    /// Specialization for when the required number of occurrences has been found.
    /// Returns the current index (minus 1) as the position of the last match.
    /// </summary>
    /// <typeparam name="array_template">The template class of the array.</typeparam>
    /// <typeparam name="other_types">The remaining types in the array (no longer examined).</typeparam>
    /// <typeparam name="helper_type_to_find">The type that was being searched for.</typeparam>
    /// <typeparam name="index">The current position in the array.</typeparam>
    template<template<typename...> class array_template, typename... other_types, typename helper_type_to_find, typename_array_size_type index>
    struct find_n_appearance_helper<array_template<other_types...>, helper_type_to_find, 0, index, false> {
        static constexpr typename_array_size_type indx = index - 1;
    };

public:
    /// <summary>
    /// The index of the Nth appearance of the specified type in the array,
    /// or npos if the type doesn't appear N times.
    /// </summary>
    static constexpr typename_array_size_type index = find_n_appearance_helper<array_type, type_to_find, counter, 0, true>::indx;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_N_APPEARANCE_H