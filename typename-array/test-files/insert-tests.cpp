#include "../typename-array-primitives/insert.hpp"

int main() {
    // Test inserting into an empty array
    using empty_array_type = typename_array<>;
    using insert_into_empty = insert<0, empty_array_type, int>::new_array;
    static_assert(std::is_same_v<insert_into_empty, typename_array<int>>,
                  "Test failed: " "\"Insert into empty array should create single element array\"");

    // Test inserting at the beginning of an array
    using array_type = typename_array<double, char>;
    using insert_at_beginning = insert<0, array_type, int>::new_array;
    static_assert(std::is_same_v<insert_at_beginning, typename_array<int, double, char>>,
                  "Test failed: " "\"Insert at beginning should place element at index 0\"");

    // Test inserting at the end of an array
    using insert_at_end = insert<2, array_type, int>::new_array;
    static_assert(std::is_same_v<insert_at_end, typename_array<double, char, int>>,
                  "Test failed: " "\"Insert at end should place element after all existing elements\"");

    // Test inserting in the middle of an array
    using insert_in_middle = insert<1, array_type, int>::new_array;
    static_assert(std::is_same_v<insert_in_middle, typename_array<double, int, char>>,
                  "Test failed: " "\"Insert in middle should place element at correct position\"");

    // Test with more complex types
    struct custom_type {};
    using complex_array = typename_array<int, double, char>;
    using insert_custom = insert<1, complex_array, custom_type>::new_array;
    static_assert(std::is_same_v<insert_custom, typename_array<int, custom_type, double, char>>,
                  "Test failed: " "\"Insert custom type should work correctly\"");

    // Test inserting multiple types into the same array
    using multi_insert_base = typename_array<int, double>;
    using first_insert = insert<1, multi_insert_base, char>::new_array;
    using second_insert = insert<0, first_insert, float>::new_array;
    static_assert(std::is_same_v<second_insert, typename_array<float, int, char, double>>,
                  "Test failed: " "\"Multiple insertions should work correctly\"");

    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    using insert_combined = insert<2, combined_array, bool>::new_array;
    
    static_assert(std::is_same_v<insert_combined, typename_array<int, double, bool, char, float>>,
                  "Test failed: " "\"Insert into combined array should work correctly\"");

    return 0;
}