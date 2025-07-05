#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_UNIQUE_ADD_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_UNIQUE_ADD_H

#include "base.hpp"
#include "insert.hpp"
#include "find.hpp"

/// <summary>
/// Adds a new type to a typename_array only if it doesn't already exist in the array.
/// </summary>
/// <typeparam name="index">The position at which to insert the new type if needed.</typeparam>
/// <typeparam name="array_type">The typename array to potentially modify.</typeparam>
/// <typeparam name="new_value_type">The new type to add if not already present.</typeparam>
template<typename_array_size_type index, typename array_type, typename new_value_type>
struct unique_add {
private:
    /// <summary>
    /// Base helper structure for the unique_add operation.
    /// </summary>
    /// <typeparam name="found">The index where the type was found, or npos if not found.</typeparam>
    /// <typeparam name="helper_array_type">The array being processed.</typeparam>
    /// <typeparam name="helper_new_value_type">The type to potentially add.</typeparam>
    template<typename_array_size_type found, typename helper_array_type, typename helper_new_value_type>
    struct unique_add_helper {
        /// <summary>
        /// When the type is already found in the array, return the original array unchanged.
        /// </summary>
        using value = helper_array_type;
    };

    /// <summary>
    /// Specialization for when the type is not found in the array.
    /// </summary>
    /// <typeparam name="helper_array_type">The array being processed.</typeparam>
    /// <typeparam name="helper_new_value_type">The type to add.</typeparam>
    template<typename helper_array_type, typename helper_new_value_type>
    struct unique_add_helper<npos, helper_array_type, helper_new_value_type> {
        /// <summary>
        /// When the type is not found, insert it at the specified index.
        /// </summary>
        using value = typename insert<index, helper_array_type, helper_new_value_type>::new_array;
    };

public:
    /// <summary>
    /// The resulting array after the unique add operation.
    /// Contains the new type only if it wasn't already present.
    /// </summary>
    using new_array = typename unique_add_helper<find<array_type, new_value_type>::index, array_type, new_value_type>::value;
};


#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_UNIQUE_ADD_H