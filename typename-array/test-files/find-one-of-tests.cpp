#include "../typename-array-primitives/find-one-of.h"

int main() {
    // Test finding in an empty array
    using empty_array = typename_array<>;
    using types_to_find = typename_array<int, double>;
    static_assert(find_one_of<empty_array, types_to_find>::index == npos,
                  "Test failed: \"Finding any type in empty array should return npos\"");

    // Test searching for types from an empty array
    using test_array = typename_array<int, char, double>;
    using empty_types_to_find = typename_array<>;
    static_assert(find_one_of<test_array, empty_types_to_find>::index == npos,
                  "Test failed: \"Finding from empty array of types should return npos\"");

    // Test finding a single type that exists
    using single_type_to_find = typename_array<char>;
    static_assert(find_one_of<test_array, single_type_to_find>::index == 1,
                  "Test failed: \"Finding a single existing type should return correct index\"");

    // Test finding a single type that doesn't exist
    using nonexistent_type = typename_array<float>;
    static_assert(find_one_of<test_array, nonexistent_type>::index == npos,
                  "Test failed: \"Finding a nonexistent type should return npos\"");

    // Test finding one of multiple types where one exists
    using multiple_types = typename_array<float, char, long>;
    static_assert(find_one_of<test_array, multiple_types>::index == 1,
                  "Test failed: \"Finding one of multiple types should return first match\"");

    // Test finding one of multiple types where none exist
    using nonexistent_types = typename_array<float, long, short>;
    static_assert(find_one_of<test_array, nonexistent_types>::index == npos,
                  "Test failed: \"Finding multiple nonexistent types should return npos\"");

    // Test finding one of multiple types where multiple exist
    using multi_match_types = typename_array<double, char, int>;
    static_assert(find_one_of<test_array, multi_match_types>::index == 0,
                  "Test failed: \"Finding multiple existing types should return first match\"");

    // Test with more complex types
    struct custom_type {};
    struct another_type {};
    using complex_array = typename_array<int, custom_type, double, another_type>;
    using complex_types_to_find = typename_array<another_type, float>;
    static_assert(find_one_of<complex_array, complex_types_to_find>::index == 3,
                  "Test failed: \"Finding custom types should work correctly\"");

    // Test with combined arrays
    using first_array = typename_array<int, double, char>;
    using second_array = typename_array<long, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    using types_to_find_combined = typename_array<float, char>;
    
    static_assert(find_one_of<combined_array, types_to_find_combined>::index == 2,
                  "Test failed: \"Finding in combined array should return correct index\"");

    return 0;
}