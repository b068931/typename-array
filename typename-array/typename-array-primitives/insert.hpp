#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INSERT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INSERT_H

#include "base.hpp"

/// <summary>
/// Inserts a new type at a specified index within a typename_array.
/// </summary>
/// <typeparam name="insert_index">The index at which to insert the new type.</typeparam>
/// <typeparam name="array_type">The typename array to insert into.</typeparam>
/// <typeparam name="new_type">The type to insert.</typeparam>
template<typename_array_size_type insert_index, typename array_type, typename new_type>
struct insert {
private:
    /// <summary>
    /// Base helper structure for inserting a type at a specific index.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="helper_array_type">Array or remaining portion being processed.</typeparam>
    /// <typeparam name="helper_new_type">The type being inserted.</typeparam>
    template<typename_array_size_type index, typename helper_array_type, typename helper_new_type>
    struct insert_helper {
        using new_array = typename_array<>;
    };

    /// <summary>
    /// Specialization for an empty array. If it was chosen, it means that
    /// insertion is at index == array_type::size.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="array_template">Empty template array.</typeparam>
    /// <typeparam name="helper_new_type">The type being inserted.</typeparam>
    template<typename_array_size_type index, template<typename...> class array_template, typename helper_new_type>
    struct insert_helper<index, array_template<>, helper_new_type> {
        /// <summary>
        /// If the array is empty, the new type is inserted immediately.
        /// </summary>
        using new_array = typename_array<helper_new_type>;
        static_assert(index == array_type::size, "Should never fail.");
    };

    /// <summary>
    /// Specialization for processing elements before the insertion point.
    /// Preserves the current element and continues recursion.
    /// </summary>
    /// <typeparam name="index">Current position in the array.</typeparam>
    /// <typeparam name="array_template">The template of the array.</typeparam>
    /// <typeparam name="helper_new_type">The type being inserted.</typeparam>
    /// <typeparam name="value_type">Current type being processed.</typeparam>
    /// <typeparam name="other_types">Remaining types in the array.</typeparam>
    template<typename_array_size_type index, template<typename...> class array_template, typename helper_new_type, typename value_type, typename... other_types>
    struct insert_helper<index, array_template<value_type, other_types...>, helper_new_type> {
        /// <summary>
        /// Combines the current value with the result of processing the remaining array.
        /// </summary>
        using next = typename combine<
            typename_array<value_type>,
            typename insert_helper<index + 1, array_template<other_types...>, helper_new_type>::new_array
        >::new_array;

        /// <summary>
        /// The resulting array after inserting the new element at current index.   
        /// </summary>
        using current_inserted = typename combine<
            typename_array<helper_new_type>,
            array_template<value_type, other_types...>
        >::new_array;

        /// <summary>
        /// A rather imperfect solution, initial implementation stopped
        /// immediately after the insertion. However, it was not portable.
        /// I was unable to think of anything better than this.
        /// </summary>
        using new_array = std::conditional_t<
            index == insert_index,
            current_inserted,
            next
        >;
    };

public:
    static_assert(insert_index <= array_type::size, "Insert index must be less than or equal to the size of the array typename_array::insert.");
    static_assert(insert_index >= 0, "Insert index must be non-negative typename_array::insert.");

    /// <summary>
    /// The resulting array after inserting the new type at the specified index.
    /// </summary>
    using new_array = typename insert_helper<0, array_type, new_type>::new_array;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INSERT_H