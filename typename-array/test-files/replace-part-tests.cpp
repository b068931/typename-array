#include "../typename-array-primitives/replace-part.hpp"
#include "../typename-array-primitives/count.hpp"

int main() {
    // Test replacing in a single-element array
    using single_element_array = typename_array<int>;
    using replaced_single = replace_part<single_element_array, 0, 0, typename_array<double>>::new_array;
    static_assert(std::is_same_v<replaced_single, typename_array<double>>,
                  "Test failed: " "\"Replacing single element should work correctly\"");

    // Test replacing at the beginning of an array
    using multi_element_array = typename_array<int, double, char, float>;
    using replaced_beginning = replace_part<multi_element_array, 0, 0, typename_array<long>>::new_array;
    static_assert(std::is_same_v<replaced_beginning, typename_array<long, double, char, float>>,
                  "Test failed: " "\"Replacing at beginning should work correctly\"");

    // Test replacing in the middle of an array
    using replaced_middle = replace_part<multi_element_array, 1, 2, typename_array<bool>>::new_array;
    static_assert(std::is_same_v<replaced_middle, typename_array<int, bool, float>>,
                  "Test failed: " "\"Replacing in middle should work correctly\"");

    // Test replacing at the end of an array
    using replaced_end = replace_part<multi_element_array, 3, 3, typename_array<short>>::new_array;
    static_assert(std::is_same_v<replaced_end, typename_array<int, double, char, short>>,
                  "Test failed: " "\"Replacing at end should work correctly\"");

    // Test replacing multiple elements with a single type
    using replaced_multiple = replace_part<multi_element_array, 1, 3, typename_array<int>>::new_array;
    static_assert(std::is_same_v<replaced_multiple, typename_array<int, int>>,
                  "Test failed: " "\"Replacing multiple elements should work correctly\"");

    // Test replacing with another array
    using replacement_array = typename_array<bool, short>;
    using replaced_with_array = replace_part<multi_element_array, 1, 2, replacement_array>::new_array;
    static_assert(std::is_same_v<replaced_with_array, typename_array<int, bool, short, float>>,
                  "Test failed: " "\"Replacing with another array should work correctly\"");

    // Test replacing entire array
    using replaced_entire = replace_part<multi_element_array, 0, 3, typename_array<long>>::new_array;
    static_assert(std::is_same_v<replaced_entire, typename_array<long>>,
                  "Test failed: " "\"Replacing entire array should work correctly\"");

    // Test replacing a section with a complex type
    struct custom_type {};
    using replaced_with_custom = replace_part<multi_element_array, 1, 2, typename_array<custom_type>>::new_array;
    static_assert(std::is_same_v<replaced_with_custom, typename_array<int, custom_type, float>>,
                  "Test failed: " "\"Replacing with custom type should work correctly\"");

    // Test replacing adjacent to other operations
    using original = typename_array<int, char, double, float, long>;
    using intermediate = replace_part<original, 1, 3, typename_array<bool>>::new_array;  // should be typename_array<int, bool, long>
    using final_array = replace_part<intermediate, 0, 0, typename_array<short>>::new_array;  // should be typename_array<short, bool, long>
    
    static_assert(std::is_same_v<final_array, typename_array<short, bool, long>>,
                  "Test failed: " "\"Sequential replace operations should work correctly\"");

    return 0;
}