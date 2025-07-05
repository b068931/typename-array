#ifndef TYPENAME_ARRAY_VALUE_H
#define TYPENAME_ARRAY_VALUE_H

#include "base.hpp"

/// <summary>
/// Wraps a compile-time value of any type in a type context.
/// This allows non-type template parameters to be used in typename arrays.
/// </summary>
/// <typeparam name="value">The compile-time value to wrap in a type.</typeparam>
template<auto value>
struct value_wrapper {
    /// <summary>
    /// The wrapped value, accessible as a static constant.
    /// </summary>
    static constexpr decltype(value) get_value = value;
};

#endif // TYPENAME_ARRAY_VALUE_H