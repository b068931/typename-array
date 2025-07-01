#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INT_TO_SYMBOLS_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INT_TO_SYMBOLS_H

#include "base.hpp"
#include "value-wrapper.hpp"

/// <summary>
/// Converts an integer value to a typename_array of value_wrapper characters.
/// </summary>
/// <typeparam name="value">The integer value to convert to character symbols.</typeparam>
template<typename_array_size_type value>
struct int_to_symbols {
private:
    /// <summary>
    /// Helper structure for converting integers to character symbols.
    /// Handles the recursive decomposition of multi-digit numbers.
    /// </summary>
    /// <typeparam name="helper_value">The current value being processed.</typeparam>
    template<typename_array_size_type helper_value>
    struct int_to_symbols_helper {
        /// <summary>
        /// Resulting array type containing character representations.
        /// For single digits (0-9), creates a simple array with one character.
        /// For multi-digit numbers, recursively processes the value.
        /// </summary>
        using array = std::conditional_t<
            (helper_value < 10),
            typename_array<value_wrapper<static_cast<char>('0' + helper_value)>>,
            typename combine<
                typename int_to_symbols<(helper_value / 10)>::array,
                typename_array<value_wrapper<static_cast<char>('0' + (helper_value % 10))>>
            >::new_array
        >;
    };

public:
    /// <summary>
    /// The resulting typename_array containing character representations of the integer.
    /// Add minus sign if necessary. 
    /// </summary>
    using array = std::conditional_t<
        (value < 0),
        typename combine<typename_array<value_wrapper<'-'>>, typename int_to_symbols_helper<-value>::array>::new_array,
        typename int_to_symbols_helper<value>::array
    >;
};

// Usually the style is that all specializations are defined inside base struct.
// However, here it is most likely impossible to implement without explicit full specialization for 0.
// This is because the recursive template specialization would not terminate for 0.
template<>
struct int_to_symbols<0> {
    /// <summary>
    /// Array containing the character '0'.
    /// </summary>
    using array = typename_array<value_wrapper<'0'>>;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_INT_TO_SYMBOLS_H