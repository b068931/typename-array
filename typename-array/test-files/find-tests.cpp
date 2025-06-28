#include "../typename-array-primitives/find.h"

int main() {
    // Test finding in an empty array
    using empty_array_type = typename_array<>;
    static_assert(find<empty_array_type, int>::index == npos,
        "Test failed: \"Finding in empty array returns npos\"");

    // Test finding in a single-type array (type exists)
    using single_type_array = typename_array<int>;
    static_assert(find<single_type_array, int>::index == 0,
        "Test failed: \"Finding existing type in single-type array returns 0\"");

    // Test finding in a single-type array (type doesn't exist)
    static_assert(find<single_type_array, double>::index == npos,
        "Test failed: \"Finding non-existing type in single-type array returns npos\"");

    // Test finding in a multi-type array (first position)
    using multi_type_array = typename_array<int, double, char, float>;
    static_assert(find<multi_type_array, int>::index == 0,
        "Test failed: \"Finding type at first position returns 0\"");

    // Test finding in a multi-type array (middle position)
    static_assert(find<multi_type_array, double>::index == 1,
        "Test failed: \"Finding type at middle position returns correct index\"");

    // Test finding in a multi-type array (last position)
    static_assert(find<multi_type_array, float>::index == 3,
        "Test failed: \"Finding type at last position returns correct index\"");

    // Test finding non-existing type in a multi-type array
    static_assert(find<multi_type_array, long>::index == npos,
        "Test failed: \"Finding non-existing type returns npos\"");

    // Test finding with duplicate types (should return first occurrence)
    using array_with_duplicates = typename_array<int, double, int, float>;
    static_assert(find<array_with_duplicates, int>::index == 0,
        "Test failed: \"Finding duplicate type returns first occurrence\"");

    return 0;
}