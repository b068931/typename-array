#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_IF_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_IF_H

#include "base.hpp"

/// <summary>
/// Finds the first type in a typename array that satisfies a given predicate.
/// </summary>
/// <typeparam name="array_type">The typename array to search in.</typeparam>
/// <typeparam name="predicate_template">A template that takes a type and provides a static boolean 'value' member.</typeparam>
template<typename array_type, template<typename> class predicate_template>
struct find_if {
private:
    /// <summary>
    /// Base case for the find_if algorithm. Called when array is empty or recursion is complete.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="found">Indicates whether a matching type has been found.</typeparam>
    /// <typeparam name="helper_array_type">The remaining part of the array to process.</typeparam>
    template<typename_array_size_type index, bool found, typename helper_array_type>
    struct find_if_helper {
        static constexpr typename_array_size_type indx = npos;
    };

    /// <summary>
    /// Recursive case for the find_if algorithm. Processes the next type in the array.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="found">Indicates whether a matching type has been found.</typeparam>
    /// <typeparam name="value_type">The current type being checked.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    /// <typeparam name="array_template">The template used for the array.</typeparam>
    template<typename_array_size_type index, typename value_type, typename... other_types, template<typename...> class array_template>
    struct find_if_helper<index, false, array_template<value_type, other_types...>> {
        static constexpr typename_array_size_type indx = find_if_helper<index + 1, predicate_template<value_type>::value, array_template<other_types...>>::indx;
    };

    /// <summary>
    /// Specialization for when a matching type has been found. Stops recursion and returns the index.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array (ignored).</typeparam>
    /// <typeparam name="array_template">The template used for the array.</typeparam>
    template<typename_array_size_type index, typename... other_types, template<typename...> class array_template>
    struct find_if_helper<index, true, array_template<other_types...>> {
        static constexpr typename_array_size_type indx = index - 1;
    };

public:
    /// <summary>
    /// The index of the first type in the array that satisfies the predicate, or npos if no such type exists.
    /// </summary>
    static constexpr typename_array_size_type index = find_if_helper<0, false, array_type>::indx;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_FIND_IF_H