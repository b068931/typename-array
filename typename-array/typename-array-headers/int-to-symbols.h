#ifndef TYPENAME_ARRAY_INT_TO_SYMBOLS_H
#define TYPENAME_ARRAY_INT_TO_SYMBOLS_H

#include "base.h"
#include "value.h"

template<typename_array_size_t val>
struct int_to_symbols {
private:
	template<typename_array_size_t helper_val>
	struct int_to_symbols_helper {
		using array = typename std::conditional<
			(helper_val < 10),
			typename_array<value<(char)('0' + helper_val)>>,
			typename combine<typename int_to_symbols<(helper_val / 10)>::array, typename_array<value<(char)('0' + (helper_val % 10))>>>::new_array
			>::type;
	};

	template<>
	struct int_to_symbols_helper<0> {
		using array = typename_array<value<'0'>>;
	};

public:
	using array = typename int_to_symbols_helper<val>::array;
};

#endif // TYPENAME_ARRAY_INT_TO_SYMBOLS_H