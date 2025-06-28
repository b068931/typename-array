#include "../typename-array-primitives/count.h"

int main() {
    // Test counting in an empty array
    using empty_array_type = typename_array<>;
    static_assert(count<empty_array_type, int>::counter == 0,
                  "Test failed: " "\"Count in empty array should be 0\"");

    // Test counting in a single-type array where the type matches
    using single_int_array = typename_array<int>;
    static_assert(count<single_int_array, int>::counter == 1,
                  "Test failed: " "\"Count for matching type in single-type array should be 1\"");

    // Test counting in a single-type array where the type doesn't match
    static_assert(count<single_int_array, double>::counter == 0,
                  "Test failed: " "\"Count for non-matching type should be 0\"");

    // Test counting in a multi-type array with no matches
    using multi_type_array = typename_array<int, double, char>;
    static_assert(count<multi_type_array, float>::counter == 0,
                  "Test failed: " "\"Count for non-existent type should be 0\"");

    // Test counting in a multi-type array with one match
    static_assert(count<multi_type_array, char>::counter == 1,
                  "Test failed: " "\"Count for single occurrence type should be 1\"");

    // Test counting in a multi-type array with multiple matches
    using multi_match_array = typename_array<int, double, int, char, int>;
    static_assert(count<multi_match_array, int>::counter == 3,
                  "Test failed: " "\"Count for multiple occurrences should match actual count\"");

    // Test with more complex types
    struct custom_type {};
    using complex_array = typename_array<int, custom_type, double, custom_type>;
    static_assert(count<complex_array, custom_type>::counter == 2,
                  "Test failed: " "\"Count for custom type should be correct\"");

    // Test with combined arrays
    using first_array = typename_array<int, double, int>;
    using second_array = typename_array<char, int, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    
    static_assert(count<combined_array, int>::counter == 3,
                  "Test failed: " "\"Count in combined array should be correct\"");

    return 0;
}