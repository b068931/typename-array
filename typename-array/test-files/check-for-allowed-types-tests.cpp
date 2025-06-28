#include "../typename-array-primitives/check-for-allowed-types.h"

namespace {
    // Define test types
    struct TypeA {};
    struct TypeB {};
    struct TypeC {};
    struct TypeD {};

    // Define a type array template for testing
    template<typename... Types>
    struct TypeArray {};
}

int main() {
    // Test 1: All types are allowed
    {
        using TestArray = TypeArray<TypeA, TypeB, TypeC>;
        using AllowedTypes = TypeArray<TypeA, TypeB, TypeC, TypeD>;

        constexpr bool result = check_for_allowed_types<TestArray, AllowedTypes>::is_valid;
        static_assert(result, "All types should be allowed");
    }

    // Test 2: Some types are not allowed
    {
        using TestArray = TypeArray<TypeA, TypeB, TypeD>;
        using AllowedTypes = TypeArray<TypeA, TypeB>;

        constexpr bool result = check_for_allowed_types<TestArray, AllowedTypes>::is_valid;
        static_assert(!result, "TypeD should not be allowed");
    }

    // Test 3: Empty array should always be valid
    {
        using EmptyArray = TypeArray<>;
        using AllowedTypes = TypeArray<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<EmptyArray, AllowedTypes>::is_valid;
        static_assert(result, "Empty array should be valid");
    }

    // Test 4: First type not allowed
    {
        using TestArray = TypeArray<TypeD, TypeA, TypeB>;
        using AllowedTypes = TypeArray<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<TestArray, AllowedTypes>::is_valid;
        static_assert(!result, "First type (TypeD) should not be allowed");
    }

    // Test 5: Middle type not allowed
    {
        using TestArray = TypeArray<TypeA, TypeD, TypeB>;
        using AllowedTypes = TypeArray<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<TestArray, AllowedTypes>::is_valid;
        static_assert(!result, "Middle type (TypeD) should not be allowed");
    }

    // Test 6: Empty allowed types list
    {
        using TestArray = TypeArray<TypeA, TypeB>;
        using EmptyAllowedTypes = TypeArray<>;

        constexpr bool result = check_for_allowed_types<TestArray, EmptyAllowedTypes>::is_valid;
        static_assert(!result, "Should fail when allowed types list is empty");
    }

    // Test 7: Duplicate types in array
    {
        using TestArray = TypeArray<TypeA, TypeB, TypeA>;
        using AllowedTypes = TypeArray<TypeA, TypeB, TypeC>;

        constexpr bool result = check_for_allowed_types<TestArray, AllowedTypes>::is_valid;
        static_assert(result, "Duplicate types should be allowed");
    }

    return 0;
}