#include "../typename-array-primitives/find-priority.h"

int main() {
    // Test with empty array to search within
    using empty_array = typename_array<>;
    using types_to_find = typename_array<int, double>;
    static_assert(find_priority<empty_array, types_to_find>::index == npos,
                  "Test failed: " "\"Finding in empty array should return npos\"");

    // Test with empty array of types to find
    using test_array = typename_array<int, double, char>;
    using empty_types_to_find = typename_array<>;
    static_assert(find_priority<test_array, empty_types_to_find>::index == npos,
                  "Test failed: " "\"Finding with empty priority list should return npos\"");

    // Test finding first priority type
    using priority_list1 = typename_array<int, float>;
    static_assert(find_priority<test_array, priority_list1>::index == 0,
                  "Test failed: " "\"Should find int at index 0\"");

    // Test finding second priority type when first not present
    using priority_list2 = typename_array<float, double>;
    static_assert(find_priority<test_array, priority_list2>::index == 1,
                  "Test failed: " "\"Should find double at index 1 when float not present\"");

    // Test when none of the priority types are found
    using priority_list3 = typename_array<long, float, short>;
    static_assert(find_priority<test_array, priority_list3>::index == npos,
                  "Test failed: " "\"Should return npos when no priority types are found\"");

    // Test with complex types
    struct custom_type1 {};
    struct custom_type2 {};
    using complex_array = typename_array<int, custom_type1, double, custom_type2>;
    using complex_priority = typename_array<custom_type2, float, custom_type1>;
    static_assert(find_priority<complex_array, complex_priority>::index == 3,
                  "Test failed: " "\"Should find custom_type2 at index 3\"");

    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    using priority_for_combined = typename_array<float, int>;
    static_assert(find_priority<combined_array, priority_for_combined>::index == 3,
                  "Test failed: " "\"Should find float at index 3 in combined array\"");

    // Test when the first priority type appears multiple times (should find first occurrence)
    using repeated_types = typename_array<char, int, double, int, float>;
    using priority_repeated = typename_array<int, float>;
    static_assert(find_priority<repeated_types, priority_repeated>::index == 1,
                  "Test failed: " "\"Should find first occurrence of int at index 1\"");

    return 0;
}