#include "../typename-array-primitives/left-to-right.hpp"
#include <type_traits>

int main() {
    // Test reversing an empty array
    using empty_array = typename_array<>;
    using empty_reversed = left_to_right<empty_array>::new_array;
    static_assert(std::is_same_v<empty_reversed, empty_array>,
                  "Test failed: \"Reversing an empty array should yield an empty array\"");

    // Test reversing a single-type array
    using single_type_array = typename_array<int>;
    using single_type_reversed = left_to_right<single_type_array>::new_array;
    static_assert(std::is_same_v<single_type_reversed, single_type_array>,
                  "Test failed: \"Reversing a single-type array should yield the same array\"");

    // Test reversing a multi-type array
    using multi_type_array = typename_array<int, double, char>;
    using expected_reversed = typename_array<char, double, int>;
    using actual_reversed = left_to_right<multi_type_array>::new_array;
    static_assert(std::is_same_v<actual_reversed, expected_reversed>,
                  "Test failed: \"Reversed multi-type array should have types in reversed order\"");

    // Test with more complex types
    struct A {};
    struct B {};
    using complex_array = typename_array<A, int, B, double>;
    using expected_complex_reversed = typename_array<double, B, int, A>;
    using actual_complex_reversed = left_to_right<complex_array>::new_array;
    static_assert(std::is_same_v<actual_complex_reversed, expected_complex_reversed>,
                  "Test failed: \"Reversed complex array should have types in reversed order\"");

    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    using expected_combined_reversed = typename_array<float, char, double, int>;
    using actual_combined_reversed = left_to_right<combined_array>::new_array;
    static_assert(std::is_same_v<actual_combined_reversed, expected_combined_reversed>,
                  "Test failed: \"Reversed combined array should have types in reversed order\"");

    return 0;
}