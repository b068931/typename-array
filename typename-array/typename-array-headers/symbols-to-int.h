#ifndef TYPENAME_ARRAY_SYMBOLS_TO_INT_H
#define TYPENAME_ARRAY_SYMBOLS_TO_INT_H

#include "base.h"
#include "static-pow.h"

template<typename... symbols>
struct symbols_to_int {
private:
	template<typename... helper_symbols>
	struct symbols_to_int_helper;

	template<typename symbol, typename... helper_symbols>
	struct symbols_to_int_helper<symbol, helper_symbols...> {
		static constexpr typename_array_size_t value = ((symbol::get_value - '0') * static_pow<10, sizeof...(helper_symbols)>::value) + symbols_to_int_helper<helper_symbols...>::value;
	};

	template<typename symbol>
	struct symbols_to_int_helper<symbol> {
		static constexpr typename_array_size_t value = (symbol::get_value - '0');
	};

public:
	static constexpr typename_array_size_t value = symbols_to_int_helper<symbols...>::value;
};

#endif // TYPENAME_ARRAY_SYMBOLS_TO_INT_H