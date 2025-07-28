#ifndef TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SYMBOLS_TO_INT_H
#define TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SYMBOLS_TO_INT_H

#include "base.hpp"
#include "get.hpp"
#include "erase.hpp"
#include "value-wrapper.hpp"
#include "static-pow.hpp"

/// <summary>
/// Converts a sequence of symbol types into an integer value.
/// Handles negative numbers by checking if the first symbol is a minus sign.
/// </summary>
/// <typeparam name="symbols_types">The sequence of symbol types to convert to an integer.</typeparam>
template<typename... symbols_types>
struct symbols_to_int {
private:
    /// <summary>
    /// Helper structure for the recursive conversion of symbols to integer.
    /// </summary>
    /// <typeparam name="helper_symbols_types">Symbol types being processed.</typeparam>
    template<typename... helper_symbols_types>
    struct symbols_to_int_helper;

    /// <summary>
    /// Recursive specialization that processes one symbol at a time.
    /// Multiplies the current symbol's value by the appropriate power of 10 based on position.
    /// </summary>
    /// <typeparam name="symbol_type">Current symbol being processed.</typeparam>
    /// <typeparam name="helper_symbols_types">Remaining symbols to process.</typeparam>
    template<typename symbol_type, typename... helper_symbols_types>
    struct symbols_to_int_helper<symbol_type, helper_symbols_types...> {
        /// <summary>
        /// Converts the current digit and adds it to the recursively processed remainder.
        /// </summary>
        static constexpr typename_array_size_type result = (symbol_type::get_value - '0') * static_pow<10, sizeof...(helper_symbols_types)>::result + symbols_to_int_helper<helper_symbols_types...>::result;
        static_assert(symbol_type::get_value >= '0' && symbol_type::get_value <= '9', "All symbols must be digits (0-9).");
    };

    /// <summary>
    /// Base case specialization for the last symbol in the sequence.
    /// </summary>
    /// <typeparam name="symbol_type">The last symbol to process.</typeparam>
    template<typename symbol_type>
    struct symbols_to_int_helper<symbol_type> {
        /// <summary>
        /// Converts the last digit to its integer value.
        /// </summary>
        static constexpr typename_array_size_type result = symbol_type::get_value - '0';
        static_assert(symbol_type::get_value >= '0' && symbol_type::get_value <= '9', "All symbols must be digits (0-9).");
    };

    /// <summary>
    /// The first symbol in the sequence, used to check for negative numbers.
    /// </summary>
    using first_symbol_type = typename get<0, typename_array<symbols_types...>>::value;

    /// <summary>
    /// Creates a reduced symbol type which:
    /// 1. Removes the minus sign if present
    /// 2. Includes a multiplier (-1 for negative numbers, 1 for positive)
    /// </summary>
    using reduced_symbols_type = std::conditional_t<
        first_symbol_type::get_value == '-',
        typename_array<typename erase<0, typename_array<symbols_types...>>::new_array, value_wrapper<-1>>,
        typename_array<typename_array<symbols_types...>, value_wrapper<1>>
    >;

public:
    /// <summary>
    /// The final integer result after converting the symbol sequence.
    /// Accounts for sign by multiplying the absolute value by the sign multiplier.
    /// </summary>
    static constexpr typename_array_size_type result = get<0, reduced_symbols_type>::value::template acquire<symbols_to_int_helper>::result * get<1, reduced_symbols_type>::value::get_value;
};

#endif // TYPENAME_ARRAY_TYPENAME_ARRAY_PRIMITIVES_SYMBOLS_TO_INT_H