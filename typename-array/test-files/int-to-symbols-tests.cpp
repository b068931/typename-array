#include "../typename-array-primitives/int-to-symbols.hpp"

int main() {
    // Test converting zero
    static_assert(std::is_same_v<
                    int_to_symbols<0>::array,
                    typename_array<value_wrapper<'0'>>
                  >, "Test failed: \"Zero should convert to '0'\"");

    // Test converting a single-digit positive number
    static_assert(std::is_same_v<
                    int_to_symbols<5>::array,
                    typename_array<value_wrapper<'5'>>
                  >, "Test failed: \"5 should convert to '5'\"");

    // Test converting a multi-digit positive number
    static_assert(std::is_same_v<
                    int_to_symbols<123>::array,
                    typename_array<value_wrapper<'1'>, value_wrapper<'2'>, value_wrapper<'3'>>
                  >, "Test failed: \"123 should convert to '1', '2', '3'\"");

    // Test converting a negative number
    static_assert(std::is_same_v<
                    int_to_symbols<-42>::array,
                    typename_array<value_wrapper<'-'>, value_wrapper<'4'>, value_wrapper<'2'>>
                  >, "Test failed: \"-42 should convert to '-', '4', '2'\"");

    // Test with larger numbers
    static_assert(std::is_same_v<
                    int_to_symbols<9876>::array,
                    typename_array<value_wrapper<'9'>, value_wrapper<'8'>, value_wrapper<'7'>, value_wrapper<'6'>>
                  >, "Test failed: \"9876 should convert to '9', '8', '7', '6'\"");

    // Test with a very large negative number
    static_assert(std::is_same_v<
                    int_to_symbols<-12345>::array,
                    typename_array<value_wrapper<'-'>, value_wrapper<'1'>, value_wrapper<'2'>, 
                                   value_wrapper<'3'>, value_wrapper<'4'>, value_wrapper<'5'>>
                  >, "Test failed: \"-12345 should convert to '-', '1', '2', '3', '4', '5'\"");

    return 0;
}