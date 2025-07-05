#include "../typename-array-primitives/typename-binder.hpp"
#include <type_traits>

// Template with fixed parameters for testing
template<typename T1, typename T2, typename T3>
struct triple_template {};

int main() {
    // Test binding a single placeholder
    using binder1 = typename_binder<typename_array, binder_placeholder<0>>;
    using bound1 = binder1::bind<int>;
    static_assert(std::is_same_v<bound1, typename_array<int>>,
                  "Test failed: \"Basic binding with a single placeholder\"");

    // Test binding multiple placeholders in order
    using binder2 = typename_binder<typename_array, 
                                  char**,
                                  binder_placeholder<0>, 
                                  binder_placeholder<1>>;
    using bound2 = binder2::bind<int, double>;
    static_assert(std::is_same_v<bound2, typename_array<char**, int, double>>,
                  "Test failed: \"Binding multiple placeholders in order\"");

    // Test binding multiple placeholders out of order
    using binder3 = typename_binder<typename_array, 
                                  binder_placeholder<1>, 
                                  binder_placeholder<0>,
                                  int**>;
    using bound3 = binder3::bind<int, double>;
    static_assert(std::is_same_v<bound3, typename_array<double, int, int**>>,
                  "Test failed: \"Binding multiple placeholders out of order\"");

    // Test binding with a mix of placeholders and concrete types
    using binder4 = typename_binder<typename_array, 
                                  int, 
                                  binder_placeholder<0>, 
                                  double>;
    using bound4 = binder4::bind<char>;
    static_assert(std::is_same_v<bound4, typename_array<int, char, double>>,
                  "Test failed: \"Binding with a mix of placeholders and concrete types\"");

    // Test binding with complex types
    struct custom_type {};
    using binder5 = typename_binder<typename_array, 
                                  custom_type, 
                                  binder_placeholder<0>>;
    using bound5 = binder5::bind<int>;
    static_assert(std::is_same_v<bound5, typename_array<custom_type, int>>,
                  "Test failed: \"Binding with complex types\"");

    // Test binding with a template that requires specific parameters
    using binder6 = typename_binder<triple_template, 
                                  binder_placeholder<0>, 
                                  binder_placeholder<1>, 
                                  binder_placeholder<2>>;
    using bound6 = binder6::bind<int, double, char>;
    static_assert(std::is_same_v<bound6, triple_template<int, double, char>>,
                  "Test failed: \"Binding with template requiring specific parameters\"");

    // Test with higher-index placeholders first
    using binder7 = typename_binder<typename_array, 
                                  binder_placeholder<2>, 
                                  binder_placeholder<1>, 
                                  binder_placeholder<0>>;
    using bound7 = binder7::bind<char, int, double>;
    static_assert(std::is_same_v<bound7, typename_array<double, int, char>>,
                  "Test failed: \"Binding with higher-index placeholders first\"");

    using binder8 = typename_binder<typename_array>;
    using bound8 = binder8::bind<int, double, char>;
    static_assert(std::is_same_v<bound8, typename_array<int, double, char>>,
        "Test failed: \"Binding with no placeholders\"");

    return 0;
}