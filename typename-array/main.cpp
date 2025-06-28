#include <iostream>
#include "./typename-array-primitives/include-all-namespace.h"

int main() {
    using namespace typename_array_primitives;
    constexpr int val = static_calculator<
        value_wrapper<'('>, value_wrapper<'1'>, value_wrapper<'1'>, value_wrapper<'+'>, value_wrapper<'2'>, value_wrapper<')'>, 
        value_wrapper<'*'>, value_wrapper<'('>, value_wrapper<'2'>, value_wrapper<'+'>, value_wrapper<'2'>, value_wrapper<')'>>::result;

    std::cout << val << std::endl; //52
}