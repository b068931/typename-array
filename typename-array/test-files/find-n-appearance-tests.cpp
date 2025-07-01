#include "../typename-array-primitives/find-n-appearance.hpp"

int main() {
    // Test finding in an empty array (should return npos)
    using empty_array_type = typename_array<>;
    static_assert(find_n_appearance<empty_array_type, int, 1>::index == npos,
                  "Test failed: " "\"Finding in empty array should return npos\"");

    // Test finding the first occurrence in a single-type array
    using single_int_array = typename_array<int>;
    static_assert(find_n_appearance<single_int_array, int, 1>::index == 0,
                  "Test failed: " "\"Index of first occurrence in single-type array should be 0\"");

    // Test finding a type that doesn't exist in the array
    static_assert(find_n_appearance<single_int_array, double, 1>::index == npos,
                  "Test failed: " "\"Finding non-existent type should return npos\"");

    // Test finding more occurrences than exist
    static_assert(find_n_appearance<single_int_array, int, 2>::index == npos,
                  "Test failed: " "\"Finding more occurrences than exist should return npos\"");

    // Test finding in a multi-type array
    using multi_type_array = typename_array<int, double, char>;
    static_assert(find_n_appearance<multi_type_array, int, 1>::index == 0,
                  "Test failed: " "\"Index of first occurrence should be correct\"");
    static_assert(find_n_appearance<multi_type_array, double, 1>::index == 1,
                  "Test failed: " "\"Index of first occurrence should be correct\"");
    static_assert(find_n_appearance<multi_type_array, char, 1>::index == 2,
                  "Test failed: " "\"Index of first occurrence should be correct\"");

    // Test finding multiple occurrences of a type
    using multi_occurrence_array = typename_array<int, double, int, char, int>;
    static_assert(find_n_appearance<multi_occurrence_array, int, 1>::index == 0,
                  "Test failed: " "\"Index of first occurrence should be correct\"");
    static_assert(find_n_appearance<multi_occurrence_array, int, 2>::index == 2,
                  "Test failed: " "\"Index of second occurrence should be correct\"");
    static_assert(find_n_appearance<multi_occurrence_array, int, 3>::index == 4,
                  "Test failed: " "\"Index of third occurrence should be correct\"");
    static_assert(find_n_appearance<multi_occurrence_array, int, 4>::index == npos,
                  "Test failed: " "\"Finding more occurrences than exist should return npos\"");

    // Test with custom types
    struct custom_type {};
    using custom_array = typename_array<int, custom_type, double, custom_type>;
    static_assert(find_n_appearance<custom_array, custom_type, 1>::index == 1,
                  "Test failed: " "\"Index of first custom type occurrence should be correct\"");
    static_assert(find_n_appearance<custom_array, custom_type, 2>::index == 3,
                  "Test failed: " "\"Index of second custom type occurrence should be correct\"");

    // Test with combined arrays
    using first_array = typename_array<int, double, int>;
    using second_array = typename_array<char, int, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    
    static_assert(find_n_appearance<combined_array, int, 1>::index == 0,
                  "Test failed: " "\"Index of first occurrence in combined array should be correct\"");
    static_assert(find_n_appearance<combined_array, int, 2>::index == 2,
                  "Test failed: " "\"Index of second occurrence in combined array should be correct\"");
    static_assert(find_n_appearance<combined_array, int, 3>::index == 4,
                  "Test failed: " "\"Index of third occurrence in combined array should be correct\"");

    return 0;
}