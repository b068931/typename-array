#ifndef TYPENAME_ARRAY_TYPENAME_BINDER_H
#define TYPENAME_ARRAY_TYPENAME_BINDER_H

#include "base.hpp"
#include "replace.hpp"
#include "insert.hpp"
#include "find.hpp"
#include "left-to-right.hpp"
#include "get.hpp"

/// <summary>
/// A placeholder type used to mark positions where types should be inserted.
/// </summary>
/// <typeparam name="index">The index of the placeholder for reference.</typeparam>
template<typename_array_size_type index>
struct placeholder {};

/// <summary>
/// A template binder that allows for flexible creation of templates with placeholder substitution.
/// Enables the creation of templates where types are inserted at specific marked positions.
/// </summary>
/// <typeparam name="templ">The template class to be instantiated after binding.</typeparam>
/// <typeparam name="other">Initial types that may contain placeholders.</typeparam>
template<template<typename, typename...> class templ, typename... other>
struct typename_binder {
private:
    /// <summary>
    /// Helper for dispatching between replacement and insertion operations.
    /// Used when a placeholder is found at a specific index.
    /// </summary>
    /// <typeparam name="index">The index where the placeholder was found.</typeparam>
    /// <typeparam name="array">The array being processed.</typeparam>
    /// <typeparam name="val">The value to insert or replace with.</typeparam>
    template<typename_array_size_type index, typename array, typename val>
    struct dispatch {
        /// <summary>
        /// The array after replacement of the placeholder at the specified index.
        /// </summary>
        using value = typename replace<index, array, val>::new_array;
    };

    /// <summary>
    /// Specialization for when no placeholder is found (npos).
    /// In this case, append the value to the end of the array.
    /// </summary>
    /// <typeparam name="array">The array being processed.</typeparam>
    /// <typeparam name="val">The value to append.</typeparam>
    template<typename array, typename val>
    struct dispatch<npos, array, val> {
        /// <summary>
        /// The array after appending the value to the end.
        /// </summary>
        using value = typename insert<array::size, array, val>::new_array;
    };

    /// <summary>
    /// Recursive helper for binding placeholders to actual types.
    /// Processes each placeholder by finding and replacing it with the corresponding type.
    /// </summary>
    /// <typeparam name="index">Current placeholder index being processed.</typeparam>
    /// <typeparam name="end">Last placeholder index to process.</typeparam>
    /// <typeparam name="array">Array containing the types to be bound.</typeparam>
    template<typename_array_size_type index, typename_array_size_type end, typename array>
    struct bind_helper {
        /// <summary>
        /// Recursively process the next placeholder.
        /// </summary>
        using temp = typename bind_helper<index + 1, end, array>::bind;
        
        /// <summary>
        /// Find and replace the current placeholder with its corresponding type.
        /// </summary>
        using bind = typename dispatch<find<temp, placeholder<index>>::index, temp, typename get<index, array>::value>::value;
    };

    /// <summary>
    /// Base case for bind_helper recursion - processes the final placeholder.
    /// </summary>
    /// <typeparam name="end">Index of the final placeholder.</typeparam>
    /// <typeparam name="array">Array containing the types to be bound.</typeparam>
    template<typename_array_size_type end, typename array>
    struct bind_helper<end, end, array> {
        /// <summary>
        /// Process the final placeholder directly using the initial template.
        /// </summary>
        using bind = typename dispatch<find<typename_array<other...>, placeholder<end>>::index, typename_array<other...>, typename get<end, array>::value>::value;
    };

public:
    /// <summary>
    /// Binds the placeholders in the template with the provided types.
    /// This creates a new template instance with placeholders replaced by actual types.
    /// </summary>
    /// <typeparam name="additional_other">The types to bind to the placeholders.</typeparam>
    template<typename... additional_other>
    using bind = typename bind_helper<0, typename_array<additional_other...>::size - 1, typename left_to_right<typename_array<additional_other...>>::new_array>::bind::template acquire<templ>;
};


#endif // TYPENAME_ARRAY_TYPENAME_BINDER_H