#include <type_traits>
#include <vector>

#include "../typename-array-primitives/base.hpp"

int main() {
    // Test empty typename_array
    using empty_array_type = typename_array<>;
    static_assert(empty_array_type::size == 0,
                  "Test failed: " "\"Empty array has size 0\"");

    // Test single-type array
    using single_type_array_type = typename_array<int>;
    static_assert(single_type_array_type::size == 1,
                  "Test failed: " "\"Single type array has size 1\"");

    // Test multi-type array
    using multi_type_array_type = typename_array<int, double, char>;
    static_assert(multi_type_array_type::size == 3,
                  "Test failed: " "\"Multi-type array has size 3\"");

    // Test acquire functionality
    using acquired_tuple_type = multi_type_array_type::acquire<std::tuple>;
    static_assert(
        std::is_same_v<acquired_tuple_type, std::tuple<int, double, char>>,
        "Test failed: " "\"Acquire transfers types correctly to tuple\"");

    // Test vector acquisition
    using acquired_vector_type = single_type_array_type::acquire<std::vector>;
    static_assert(std::is_same_v<acquired_vector_type, std::vector<int>>,
                  "Test failed: "
                  "\"Acquire transfers types correctly to vector\"");

    // Test combining arrays
    using first_array_type = typename_array<int, float>;
    using second_array_type = typename_array<char, double>;
    using combined_array_type = combine<first_array_type, second_array_type>::new_array;

    static_assert(combined_array_type::size == 4,
                  "Test failed: " "\"Combined array has correct size\"");
    static_assert(
        std::is_same_v<combined_array_type, typename_array<
                             int, float, char, double>>,
        "Test failed: " "\"Combined array has correct types\"");

    // Test combining with empty array
    using combined_with_empty_type = combine<first_array_type, empty_array_type>::new_array;
    static_assert(combined_with_empty_type::size == 2,
                  "Test failed: "
                  "\"Combining with empty array preserves original size\"");
    static_assert(
        std::is_same_v<combined_with_empty_type, first_array_type>,
        "Test failed: "
        "\"Combining with empty array preserves original types\"");

    // Test empty + empty
    using empty_combined_type = combine<empty_array_type, empty_array_type>::new_array;
    static_assert(empty_combined_type::size == 0,
                  "Test failed: " "\"Empty combined with empty is empty\"");

    return 0;
}