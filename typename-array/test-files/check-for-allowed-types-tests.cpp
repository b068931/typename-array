#include "../typename-array-primitives/check-for-allowed-types.h"

namespace {
    // Define test types
    struct TypeA {};
    struct TypeB {};
    struct TypeC {};
    struct TypeD {};
}

int main() {
    // Test 1: All types are allowed
    {
        using test_array = typename_array<TypeA, TypeB, TypeC>;
        using allowed_types = typename_array<TypeA, TypeB, TypeC, TypeD>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(result, "All types should be allowed");
    }

    // Test 2: Some types are not allowed
    {
        using test_array = typename_array<TypeA, TypeB, TypeD>;
        using allowed_types = typename_array<TypeA, TypeB>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(!result, "TypeD should not be allowed");
    }

    // Test 3: Empty array should always be valid
    {
        using EmptyArray = typename_array<>;
        using allowed_types = typename_array<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<EmptyArray, allowed_types>::is_valid;
        static_assert(result, "Empty array should be valid");
    }

    // Test 4: First type not allowed
    {
        using test_array = typename_array<TypeD, TypeA, TypeB>;
        using allowed_types = typename_array<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(!result, "First type (TypeD) should not be allowed");
    }

    // Test 5: Middle type not allowed
    {
        using test_array = typename_array<TypeA, TypeD, TypeB>;
        using allowed_types = typename_array<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(!result, "Middle type (TypeD) should not be allowed");
    }

    // Test 6: Empty allowed types list
    {
        using test_array = typename_array<TypeA, TypeB>;
        using allowed_types = typename_array<>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(!result, "Should fail when allowed types list is empty");
    }

    // Test 7: Duplicate types in array
    {
        using test_array = typename_array<TypeA, TypeB, TypeA>;
        using allowed_types = typename_array<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<test_array, allowed_types>::is_valid;
        static_assert(result, "Duplicate types should be allowed");
    }

    return 0;
}