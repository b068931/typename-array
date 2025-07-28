#include "../typename-array-primitives/apply.hpp"

namespace {
    // Test functor that adds a pointer to each type
    template<typename T, typename_array_size_type Index>
    struct add_pointer_functor {
        using new_value = T *;
    };

    // Test functor that applies const based on index (odd indices get const)
    template<typename T, typename_array_size_type Index>
    struct index_based_const_functor {
        using new_value = typename std::conditional<
            Index % 2 == 0,
            T,          // Even indices: keep type as-is
            const T     // Odd indices: add const
        >::type;
    };

    // Test functor that applies different transformations based on index modulo 3
    template<typename T, typename_array_size_type Index>
    struct type_selector_functor {
        using new_value = typename std::conditional<
            Index % 3 == 0,
            T *,                     // Index % 3 == 0: pointer
            typename std::conditional<
            Index % 3 == 1,
            T &,                 // Index % 3 == 1: reference
            const T             // Index % 3 == 2: const
            >::type
        >::type;
    };
}

int main() {
    // Test 1: Apply to empty array
    using empty_array = typename_array<>;
    using empty_result = apply<empty_array, add_pointer_functor>::new_array;
    static_assert(std::is_same_v<empty_result, typename_array<>>, "Empty array test failed");
    
    // Test 2: Apply to single element array
    using single_array = typename_array<int>;
    using single_result = apply<single_array, add_pointer_functor>::new_array;
    static_assert(std::is_same_v<single_result, typename_array<int*>>, "Single element test failed");
    
    // Test 3: Apply to multiple element array
    using multi_array = typename_array<int, float, char, double>;
    using multi_result = apply<multi_array, add_pointer_functor>::new_array;
    static_assert(std::is_same_v<multi_result, typename_array<int*, float*, char*, double*>>, 
                  "Multiple elements test failed");
    
    // Test 4: Using index in the transformation
    using index_result = apply<multi_array, index_based_const_functor>::new_array;
    using expected_index_result = typename_array<int, const float, char, const double>;
    static_assert(std::is_same_v<index_result, expected_index_result>, 
                  "Index-based transformation test failed");
    
    // Test 5: Complex index-based transformation
    using complex_array = typename_array<int, char, double, float, short, long>;
    using complex_result = apply<complex_array, type_selector_functor>::new_array;
    using expected_complex_result = typename_array<
        int*,           // Index 0: pointer
        char&,          // Index 1: reference
        const double,   // Index 2: const
        float*,         // Index 3: pointer
        short&,         // Index 4: reference
        const long      // Index 5: const
    >;
    static_assert(std::is_same_v<complex_result, expected_complex_result>, 
                  "Complex transformation test failed");
    
    return 0;
}