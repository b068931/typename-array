#include <cstdint>
#include "../typename-array-primitives/sum.hpp"

// Functor template that extracts a specific value from a type
template <typename T>
struct type_value;

// Specializations for different types
template <>
struct type_value<int> {
    static constexpr int value = 10;
};

template <>
struct type_value<double> {
    static constexpr double value = 20.5;
};

template <>
struct type_value<char> {
    static constexpr int value = 5;
};

template <>
struct type_value<float> {
    static constexpr float value = 15.25f;
};

// Functor that returns a type's size
template <typename T>
struct type_size {
    static constexpr std::size_t value = sizeof(T);
};

int main() {
    // Test sum in an empty array
    using empty_array_type = typename_array<>;
    static_assert(sum<empty_array_type, type_value, int>::new_value == 0,
                  "Test failed: \"Sum of empty array should be 0\"");

    // Test sum in a single-type array
    using single_type_array = typename_array<int>;
    static_assert(sum<single_type_array, type_value, int>::new_value == 10,
                  "Test failed: \"Sum of single-type array should equal type's value\"");

    // Test sum in a multi-type array
    using multi_type_array = typename_array<int, double, char>;
    static_assert(sum<multi_type_array, type_value, double>::new_value == 35.5,
                  "Test failed: \"Sum of multi-type array should be correct (10 + 20.5 + 5)\"");

    // Test sum with different functor (type size)
    static_assert(sum<multi_type_array, type_size, std::size_t>::new_value == sizeof(int) + sizeof(double) + sizeof(char),
                  "Test failed: \"Sum using type_size functor should equal sum of all type sizes\"");

    return 0;
}