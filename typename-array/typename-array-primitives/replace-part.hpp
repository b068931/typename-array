#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_PART_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_PART_H

#include "base.hpp"
#include "cut.hpp"

/// <summary>
/// Replaces a section of a typename_array with another type or array.
/// </summary>
/// <typeparam name="array_type">The original typename array to modify.</typeparam>
/// <typeparam name="start">The starting index of the section to replace (inclusive).</typeparam>
/// <typeparam name="end">The ending index of the section to replace (inclusive).</typeparam>
/// <typeparam name="to_place_type">The type (must be wrapped into typename_array) or array to insert in place of the removed section.</typeparam>
template<typename array_type, typename_array_size_type start, typename_array_size_type end, typename to_place_type>
struct replace_part {
    /// <summary>
    /// The resulting array type after replacement.
    /// Combines three parts: the section before the replaced range, 
    /// the inserted type, and the section after the replaced range.
    /// </summary>
    using new_array = typename combine<
        typename combine<typename cut<0, (start - 1), array_type>::new_array, to_place_type>::new_array,
        typename cut<end + 1, array_type::size - 1, array_type>::new_array>::new_array;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_REPLACE_PART_H