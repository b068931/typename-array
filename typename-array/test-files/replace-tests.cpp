#include "../typename-array-primitives/replace.hpp"

int main() {
    // Test replacing in a single-type array
    using single_int_array = typename_array<int>;
    using replaced_single = replace<0, single_int_array, double>::new_array;
    static_assert(std::is_same_v<replaced_single, typename_array<double>>,
                  "Test failed: " "\"Replacing in a single-type array should work\"");

    // Test replacing the first element in a multi-type array
    using multi_type_array = typename_array<int, double, char>;
    using replaced_first = replace<0, multi_type_array, float>::new_array;
    static_assert(std::is_same_v<replaced_first, typename_array<float, double, char>>,
                  "Test failed: " "\"Replacing first element should work\"");

    // Test replacing a middle element in a multi-type array
    using replaced_middle = replace<1, multi_type_array, float>::new_array;
    static_assert(std::is_same_v<replaced_middle, typename_array<int, float, char>>,
                  "Test failed: " "\"Replacing middle element should work\"");

    // Test replacing the last element in a multi-type array
    using replaced_last = replace<2, multi_type_array, float>::new_array;
    static_assert(std::is_same_v<replaced_last, typename_array<int, double, float>>,
                  "Test failed: " "\"Replacing last element should work\"");

    // Test with more complex types
    struct custom_type_a {};
    struct custom_type_b {};
    using complex_array = typename_array<int, custom_type_a, double>;
    using replaced_complex = replace<1, complex_array, custom_type_b>::new_array;
    static_assert(std::is_same_v<replaced_complex, typename_array<int, custom_type_b, double>>,
                  "Test failed: " "\"Replacing custom types should work\"");

    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    
    using replaced_combined = replace<2, combined_array, bool>::new_array;
    static_assert(std::is_same_v<replaced_combined, typename_array<int, double, bool, float>>,
                  "Test failed: " "\"Replacing in combined array should work\"");

    return 0;
}