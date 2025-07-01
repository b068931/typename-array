#include <type_traits>

#include "../typename-array-primitives/cut.hpp"

int main() {
    // Test multi-type array for cutting
    using test_array = typename_array<int, double, char, float, long>;
    
    // Test cutting a range from the middle
    using middle_cut = cut<1, 3, test_array>::new_array;
    static_assert(middle_cut::size == 3,
                  "Test failed: \"Cut from middle has correct size\"");
    static_assert(
        std::is_same_v<middle_cut, typename_array<double, char, float>>,
        "Test failed: \"Cut from middle has correct types\"");
    
    // Test cutting a single element
    using single_cut = cut<2, 2, test_array>::new_array;
    static_assert(single_cut::size == 1,
                  "Test failed: \"Single element cut has correct size\"");
    static_assert(
        std::is_same_v<single_cut, typename_array<char>>,
        "Test failed: \"Single element cut has correct type\"");
    
    // Test cutting the entire array
    using full_cut = cut<0, 4, test_array>::new_array;
    static_assert(full_cut::size == 5,
                  "Test failed: \"Full array cut has correct size\"");
    static_assert(
        std::is_same_v<full_cut, test_array>,
        "Test failed: \"Full array cut preserves all types\"");
    
    return 0;
}