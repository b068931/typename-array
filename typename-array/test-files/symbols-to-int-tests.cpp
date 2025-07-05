#include "../typename-array-primitives/value-wrapper.hpp"
#include "../typename-array-primitives/symbols-to-int.hpp"

int main() {
    // Test converting a single digit
    static_assert(symbols_to_int<value_wrapper<'5'>>::result == 5,
                  "Test failed: Single digit conversion");

    // Test converting multiple digits
    static_assert(symbols_to_int<value_wrapper<'1'>, value_wrapper<'2'>, value_wrapper<'3'>>::result == 123,
                  "Test failed: Multiple digit conversion");

    // Test converting multiple digits
    static_assert(symbols_to_int<value_wrapper<'1'>, value_wrapper<'2'>>::result == 12,
                  "Test failed: Multiple digit conversion");

    // Test converting a negative number
    static_assert(symbols_to_int<value_wrapper<'-'>, value_wrapper<'4'>, value_wrapper<'2'>>::result == -42,
                  "Test failed: Negative number conversion");

    // Test converting zero
    static_assert(symbols_to_int<value_wrapper<'0'>>::result == 0,
                  "Test failed: Zero conversion");

    // Test larger numbers
    static_assert(symbols_to_int<value_wrapper<'9'>, value_wrapper<'8'>, value_wrapper<'7'>, value_wrapper<'6'>, value_wrapper<'5'>>::result == 98765,
                  "Test failed: Large number conversion");

    // Test with leading zeros (should ignore leading zeros)
    static_assert(symbols_to_int<value_wrapper<'0'>, value_wrapper<'4'>, value_wrapper<'2'>>::result == 42,
                  "Test failed: Number with leading zeros");

    // Test negative number with multiple digits
    static_assert(symbols_to_int<value_wrapper<'-'>, value_wrapper<'1'>, value_wrapper<'2'>, value_wrapper<'3'>, value_wrapper<'4'>, value_wrapper<'5'>>::result == -12345,
                  "Test failed: Large negative number conversion");

    // Test boundary cases
    static_assert(symbols_to_int<value_wrapper<'3'>, value_wrapper<'2'>, value_wrapper<'7'>, value_wrapper<'6'>, value_wrapper<'7'>>::result == 32767,
                  "Test failed: Maximum 16-bit signed integer");

    return 0;
}