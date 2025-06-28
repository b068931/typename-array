#include <type_traits>

#include "../typename-array-primitives/find-if.h"

namespace {
    // Create predicates for testing
    template<typename T>
    struct is_int {
        static constexpr bool value = std::is_same<T, int>::value;
    };

    template<typename T>
    struct is_floating_point {
        static constexpr bool value = std::is_floating_point<T>::value;
    };

    template<typename T>
    struct always_false {
        static constexpr bool value = false;
    };

    template<typename T>
    struct always_true {
        static constexpr bool value = true;
    };

    struct custom_type {};
    
    template<typename T>
    struct is_custom_type {
        static constexpr bool value = std::is_same<T, custom_type>::value;
    };
}

int main() {
    // Test with an empty array (should return npos)
    using empty_array = typename_array<>;
    static_assert(find_if<empty_array, is_int>::index == npos,
                  "Test failed: Find in empty array should return npos");

    // Test with a single-type array where predicate matches
    using single_int_array = typename_array<int>;
    static_assert(find_if<single_int_array, is_int>::index == 0,
                  "Test failed: Find with matching predicate should return 0");

    // Test with a single-type array where predicate doesn't match
    static_assert(find_if<single_int_array, is_floating_point>::index == npos,
                  "Test failed: Find with non-matching predicate should return npos");

    // Test with a multi-type array where no types match
    using multi_type_array = typename_array<int, char, bool>;
    static_assert(find_if<multi_type_array, is_floating_point>::index == npos,
                  "Test failed: Find with no matches should return npos");

    // Test with a multi-type array where one type matches
    using multi_type_array_with_float = typename_array<int, double, char>;
    static_assert(find_if<multi_type_array_with_float, is_floating_point>::index == 1,
                  "Test failed: Find should return index of first match");

    // Test with a multi-type array where multiple types match (should return first match)
    using multi_match_array = typename_array<char, int, double, float, int>;
    static_assert(find_if<multi_match_array, is_int>::index == 1,
                  "Test failed: Find should return index of first match when multiple matches exist");
    static_assert(find_if<multi_match_array, is_floating_point>::index == 2,
                  "Test failed: Find should return index of first floating point type");

    // Test with custom types
    using array_with_custom = typename_array<int, custom_type, double>;
    static_assert(find_if<array_with_custom, is_custom_type>::index == 1,
                  "Test failed: Find should work with custom types");

    // Test with always_true predicate (should return first element)
    static_assert(find_if<multi_type_array, always_true>::index == 0,
                  "Test failed: Find with always_true should return 0");

    // Test with always_false predicate (should return npos)
    static_assert(find_if<multi_type_array, always_false>::index == npos,
                  "Test failed: Find with always_false should return npos");

    // Test with combined arrays
    using first_array = typename_array<char, bool>;
    using second_array = typename_array<int, double>;
    using combined_array = combine<first_array, second_array>::new_array;
    
    static_assert(find_if<combined_array, is_int>::index == 2,
                  "Test failed: Find in combined array should return correct index");
    static_assert(find_if<combined_array, is_floating_point>::index == 3,
                  "Test failed: Find in combined array should return correct index for floating point");

    return 0;
}