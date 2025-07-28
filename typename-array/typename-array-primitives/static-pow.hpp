#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_STATIC_POW_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_STATIC_POW_H

#include "base.hpp"

/// <summary>
/// Calculates the power of a value at compile time.
/// </summary>
/// <typeparam name="value">The base value to be raised to a power.</typeparam>
/// <typeparam name="counter">The exponent to raise the base value to.</typeparam>
template<typename_array_size_type value, typename_array_size_type counter>
struct static_pow {
private:
    /// <summary>
    /// Helper structure for calculating power using recursive template instantiation.
    /// </summary>
    /// <typeparam name="helper_value">The base value being raised to a power.</typeparam>
    /// <typeparam name="helper_counter">The remaining exponent to process.</typeparam>
    template<typename_array_size_type helper_value, typename_array_size_type helper_counter>
    struct static_pow_helper {
        /// <summary>
        /// Recursively calculates the power by multiplying the base value by the result of the next lower power.
        /// </summary>
        static constexpr typename_array_size_type result = helper_value * static_pow<helper_value, helper_counter - 1>::result;
    };

    /// <summary>
    /// Specialization for the base case when exponent is zero.
    /// Any number raised to the power of zero equals one.
    /// </summary>
    /// <typeparam name="helper_value">The base value (not used in calculation when exponent is zero).</typeparam>
    template<typename_array_size_type helper_value>
    struct static_pow_helper<helper_value, 0> {
        /// <summary>
        /// The result of any number raised to the power of zero is one.
        /// </summary>
        static constexpr typename_array_size_type result = 1;
    };

public:
    static_assert(counter >= 0, "Exponent must be non-negative.");

    /// <summary>
    /// The final result of raising the base value to the specified power.
    /// </summary>
    static constexpr typename_array_size_type result = static_pow_helper<value, counter>::result;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_STATIC_POW_H