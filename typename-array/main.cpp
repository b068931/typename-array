#include <iostream>
#include "./typename-array-headers/include-all-namespace.h"

int main() {
    int val = typename_array::static_calculator<
        typename_array::value_wrapper<'('>,
        typename_array::value_wrapper<'1'>,
        typename_array::value_wrapper<'1'>,
        typename_array::value_wrapper<'+'>,
        typename_array::value_wrapper<'2'>,
        typename_array::value_wrapper<')'>,
        typename_array::value_wrapper<'*'>,
        typename_array::value_wrapper<'('>,
        typename_array::value_wrapper<'2'>,
        typename_array::value_wrapper<'+'>,
        typename_array::value_wrapper<'2'>,
        typename_array::value_wrapper<')'>
    >::result;

    //int val = typename_array::static_calc <
 //       typename_array::value<'('>,
    //	typename_array::value<'2'>,
    //	typename_array::value<'/'>,
    //	typename_array::value<'2'>,
    //	typename_array::value<')'>,
    //	typename_array::value<'+'>,
    //	typename_array::value<'3'>
    //>::result;

    std::cout << val << std::endl;
}