#include "../typename-array-primitives/value-wrapper.hpp"
#include "../typename-array-primitives/sort.hpp"

// Define predicates for testing
template<typename T, typename U>
struct size_less {
    static constexpr bool value = sizeof(T) < sizeof(U);
};

template<typename T, typename U>
struct size_greater {
    static constexpr bool value = sizeof(T) > sizeof(U);
};

template<typename T, typename U>
struct size_less_wrapper {
    static constexpr bool value = T::get_value < U::get_value;
};

// Custom types with different sizes for testing
struct Small { char x; };              // 1 byte
struct Medium { int x; };              // 4 bytes
struct Large { double x[2]; };         // 16 bytes

int main() {
    // Test sorting an empty array
    using empty_array = typename_array<>;
    static_assert(std::is_same_v<sort<empty_array, size_less>::new_array, empty_array>,
                  "Test failed: " "\"Empty array should remain unchanged after sorting\"");

    // Test sorting a single-element array
    using single_type_array = typename_array<int>;
    static_assert(std::is_same_v<sort<single_type_array, size_less>::new_array, single_type_array>,
                  "Test failed: " "\"Single-element array should remain unchanged after sorting\"");

    // Test sorting a two-element array where elements are already sorted
    using sorted_two_types = typename_array<char, int>; // char < int by size
    static_assert(std::is_same_v<sort<sorted_two_types, size_less>::new_array, sorted_two_types>,
                  "Test failed: " "\"Already sorted two-element array should remain unchanged\"");

    // Test sorting a two-element array where elements need sorting
    using unsorted_two_types = typename_array<int, char>; // int > char by size
    using expected_sorted_two = typename_array<char, int>;
    static_assert(std::is_same_v<sort<unsorted_two_types, size_less>::new_array, expected_sorted_two>,
                  "Test failed: " "\"Two-element array should be correctly sorted\"");

    // Test sorting a multi-element array
    using multi_type_array = typename_array<int, char, double, float>;
    using expected_size_sorted = typename_array<char, float, int, double>; // Sorted by size
    static_assert(std::is_same_v<sort<multi_type_array, size_less>::new_array, expected_size_sorted>,
                  "Test failed: " "\"Multi-element array should be correctly sorted by size\"");

    // Test sorting with a different predicate (size_greater)
    using expected_reverse_sorted = typename_array<double, float, int, char>; // Sorted by descending size
    static_assert(std::is_same_v<sort<multi_type_array, size_greater>::new_array, expected_reverse_sorted>,
                  "Test failed: " "\"Multi-element array should be correctly sorted by descending size\"");

    // Test sorting with custom types
    using custom_type_array = typename_array<Medium, Small, Large>;
    using expected_custom_sorted = typename_array<Small, Medium, Large>; // Sorted by size
    static_assert(std::is_same_v<sort<custom_type_array, size_less>::new_array, expected_custom_sorted>,
                  "Test failed: " "\"Custom type array should be correctly sorted by size\"");

    // Test sorting with duplicate types
    using array_with_duplicates = typename_array<int, char, int, double, char>;
    using expected_duplicates_sorted = typename_array<char, char, int, int, double>; // Sorted by size
    static_assert(std::is_same_v<sort<array_with_duplicates, size_less>::new_array, expected_duplicates_sorted>,
                  "Test failed: " "\"Array with duplicate types should be correctly sorted\"");

    // Test sorting a large array
    using large_array = typename_array<double, int, char, float, Small, Medium, Large>;
    using expected_large_sorted = typename_array<Small, char, Medium, float, int, double, Large>; // Sorted by size
    static_assert(std::is_same_v<sort<large_array, size_less>::new_array, expected_large_sorted>,
                  "Test failed: " "\"Large array should be correctly sorted by size\"");
    
    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    using expected_combined_sorted = typename_array<char, float, int, double>; // Sorted by size
    
    static_assert(std::is_same_v<sort<combined_array, size_less>::new_array, expected_combined_sorted>,
                  "Test failed: " "\"Combined array should be correctly sorted by size\"");

    // Test with value_wrapper
    using value_wrapper_array = typename_array<value_wrapper<534>, value_wrapper<6>, value_wrapper<2>, value_wrapper<-3>, value_wrapper<2.1>, value_wrapper<0>>;
    using value_wrapper_array_expected = typename_array<value_wrapper<-3>, value_wrapper<0>, value_wrapper<2>, value_wrapper<2.1>, value_wrapper<6>, value_wrapper<534>>;
    static_assert(std::is_same_v<sort<value_wrapper_array, size_less_wrapper>::new_array, value_wrapper_array_expected>, 
        "Test failed: " "\"Value wrapper array should be correctly sorted by descending size\"");

    return 0;
}