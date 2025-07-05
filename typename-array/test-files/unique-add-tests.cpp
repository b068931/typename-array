#include "../typename-array-primitives/unique-add.hpp"
#include "../typename-array-primitives/count.hpp"

int main() {
    // Test adding to an empty array
    using empty_array = typename_array<>;
    using empty_with_int = unique_add<0, empty_array, int>::new_array;
    static_assert(count<empty_with_int, int>::counter == 1,
                  "Test failed: \"Adding a type to an empty array should work\"");

    // Test adding a new type to a non-empty array
    using single_array = typename_array<int>;
    using with_double = unique_add<1, single_array, double>::new_array;
    static_assert(count<with_double, double>::counter == 1,
                  "Test failed: \"Adding a new type should work\"");
    static_assert(count<with_double, int>::counter == 1,
                  "Test failed: \"Original type should be preserved\"");

    // Test adding a type that already exists
    using duplicate_add = unique_add<0, single_array, int>::new_array;
    static_assert(std::is_same_v<duplicate_add, single_array>,
                  "Test failed: \"Adding an existing type should return the original array\"");
    static_assert(count<duplicate_add, int>::counter == 1,
                  "Test failed: \"Duplicate type should not be added\"");

    // Test adding at different positions
    using multi_array = typename_array<char, double, float>;
    
    // Add at beginning
    using add_at_start = unique_add<0, multi_array, int>::new_array;
    static_assert(std::is_same_v<add_at_start, typename_array<int, char, double, float>>,
                  "Test failed: \"Adding at beginning should insert correctly\"");
    
    // Add in middle
    using add_in_middle = unique_add<2, multi_array, int>::new_array;
    static_assert(std::is_same_v<add_in_middle, typename_array<char, double, int, float>>,
                  "Test failed: \"Adding in middle should insert correctly\"");
    
    // Add at end
    using add_at_end = unique_add<3, multi_array, int>::new_array;
    static_assert(std::is_same_v<add_at_end, typename_array<char, double, float, int>>,
                  "Test failed: \"Adding at end should insert correctly\"");

    // Test with custom type
    struct custom_type {};
    using custom_array = typename_array<int, double>;
    using with_custom = unique_add<1, custom_array, custom_type>::new_array;
    static_assert(std::is_same_v<with_custom, typename_array<int, custom_type, double>>,
                  "Test failed: \"Should work with custom types\"");

    // Test adding a type that exists but at a different index
    using has_int = typename_array<double, int, char>;
    using add_int_again = unique_add<0, has_int, int>::new_array;
    static_assert(std::is_same_v<add_int_again, has_int>,
                  "Test failed: \"Should not add when type exists at different index\"");

    // Test with already combined arrays
    using first_array = typename_array<int, double>;
    using second_array = typename_array<char, float>;
    using combined = combine<first_array, second_array>::new_array;
    using unique_added = unique_add<2, combined, bool>::new_array;
    
    static_assert(count<unique_added, bool>::counter == 1,
                  "Test failed: \"Should add unique type to combined array\"");
    static_assert(count<unique_added, int>::counter == 1 && 
                  count<unique_added, double>::counter == 1 &&
                  count<unique_added, char>::counter == 1 &&
                  count<unique_added, float>::counter == 1,
                  "Test failed: \"All original types should be preserved\"");

    return 0;
}