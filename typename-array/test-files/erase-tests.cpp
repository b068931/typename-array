#include <type_traits>

#include "../typename-array-primitives/erase.hpp"
#include "../typename-array-primitives/count.hpp"

int main() {
    // Test erasing the only element from a single-element array
    using single_int_array = typename_array<int>;
    using empty_after_erase = erase<0, single_int_array>::new_array;
    static_assert(std::is_same_v<empty_after_erase, typename_array<>>,
                  "Test failed: \"Erasing only element should yield empty array\"");

    // Test erasing the first element from a multi-element array
    using multi_type_array = typename_array<int, double, char>;
    using first_erased = erase<0, multi_type_array>::new_array;
    static_assert(std::is_same_v<first_erased, typename_array<double, char>>,
                  "Test failed: \"Erasing first element should remove only that element\"");

    // Test erasing a middle element from a multi-element array
    using middle_erased = erase<1, multi_type_array>::new_array;
    static_assert(std::is_same_v<middle_erased, typename_array<int, char>>,
                  "Test failed: \"Erasing middle element should remove only that element\"");

    // Test erasing the last element from a multi-element array
    using last_erased = erase<2, multi_type_array>::new_array;
    static_assert(std::is_same_v<last_erased, typename_array<int, double>>,
                  "Test failed: \"Erasing last element should remove only that element\"");

    // Test with more complex types
    struct custom_type {};
    using complex_array = typename_array<int, custom_type, double, custom_type>;
    using complex_erased = erase<1, complex_array>::new_array;
    static_assert(std::is_same_v<complex_erased, typename_array<int, double, custom_type>>,
                  "Test failed: \"Erasing with complex types should work correctly\"");
    static_assert(count<complex_erased, custom_type>::counter == 1,
                  "Test failed: \"Count should be reduced after erasing one occurrence\"");

    // Test erasing from an array with duplicate types
    using array_with_duplicates = typename_array<int, double, int, char, int>;
    using erased_duplicate = erase<2, array_with_duplicates>::new_array;
    static_assert(std::is_same_v<erased_duplicate, typename_array<int, double, char, int>>,
                  "Test failed: \"Erasing specific duplicate should work correctly\"");
    static_assert(count<erased_duplicate, int>::counter == 2,
                  "Test failed: \"Count should be reduced by one after erasing one duplicate\"");

    return 0;
}