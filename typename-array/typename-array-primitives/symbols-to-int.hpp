#ifndef TYPENAME_ARRAY_SYMBOLS_TO_INT_H
#define TYPENAME_ARRAY_SYMBOLS_TO_INT_H

#include "base.hpp"
#include "static-pow.hpp"

template<typename... symbols>
struct symbols_to_int {
private:
    template<typename... helper_symbols>
    struct symbols_to_int_helper;

    template<typename symbol, typename... helper_symbols>
    struct symbols_to_int_helper<symbol, helper_symbols...> {
        static constexpr typename_array_size_type result = ((symbol::get_value - '0') * static_pow<10, sizeof...(helper_symbols)>::result) + symbols_to_int_helper<helper_symbols...>::result;
    };

    template<typename symbol>
    struct symbols_to_int_helper<symbol> {
        static constexpr typename_array_size_type result = (symbol::get_value - '0');
    };

public:
    static constexpr typename_array_size_type result = symbols_to_int_helper<symbols...>::result;
};

#endif // TYPENAME_ARRAY_SYMBOLS_TO_INT_H