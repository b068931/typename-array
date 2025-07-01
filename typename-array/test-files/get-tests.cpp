#include "../typename-array-primitives/get.hpp"

int main() {
    // Test getting from a single-type array
    using single_int_array = typename_array<int>;
    static_assert(std::is_same_v<get<0, single_int_array>::value, int>,
                  "Test failed: " "\"Getting element from single-type array should return correct type\"");

    // Test getting from different positions in a multi-type array
    using multi_type_array = typename_array<int, double, char>;
    static_assert(std::is_same_v<get<0, multi_type_array>::value, int>,
                  "Test failed: " "\"Get first element from multi-type array should return correct type\"");
    static_assert(std::is_same_v<get<1, multi_type_array>::value, double>,
                  "Test failed: " "\"Get middle element from multi-type array should return correct type\"");
    static_assert(std::is_same_v<get<2, multi_type_array>::value, char>,
                  "Test failed: " "\"Get last element from multi-type array should return correct type\"");

    // Test with more complex types
    struct custom_type {};
    class another_type {};
    using complex_array = typename_array<int, custom_type, another_type, double>;
    static_assert(std::is_same_v<get<1, complex_array>::value, custom_type>,
                  "Test failed: " "\"Get should work with custom struct types\"");
    static_assert(std::is_same_v<get<2, complex_array>::value, another_type>,
                  "Test failed: " "\"Get should work with custom class types\"");

    // Test with combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined_array = combine<first_array, second_array>::new_array;
    
    static_assert(std::is_same_v<get<0, combined_array>::value, int>,
                  "Test failed: " "\"Get from combined array should return correct type from first array\"");
    static_assert(std::is_same_v<get<2, combined_array>::value, char>,
                  "Test failed: " "\"Get from combined array should return correct type from second array\"");
    static_assert(std::is_same_v<get<3, combined_array>::value, float>,
                  "Test failed: " "\"Get from combined array should return correct type from second array end\"");

    // The following would fail to compile due to index out of bounds:
    // static_assert(std::is_same_v<get<3, multi_type_array>::value, void>,
    //              "This should not compile due to index out of bounds");

    return 0;
}