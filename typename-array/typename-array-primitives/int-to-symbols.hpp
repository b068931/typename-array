#ifndef TYPENAME_ARRAY_INT_TO_SYMBOLS_H
#define TYPENAME_ARRAY_INT_TO_SYMBOLS_H

#include "base.hpp"
#include "value-wrapper.hpp"

template<typename_array_size_type value>
struct int_to_symbols {
private:
	template<typename_array_size_type helper_value>
	struct int_to_symbols_helper {
		using array = std::conditional_t<
			(helper_value < 10),
			typename_array<value_wrapper<static_cast<char>('0' + helper_value)>>,
			typename combine<
			    typename int_to_symbols<(helper_value / 10)>::array,
	            typename_array<value_wrapper<static_cast<char>('0' + (helper_value % 10))>>
	        >::new_array
	    >;
	};

public:
	using array = typename int_to_symbols_helper<value>::array;
};

// Usually the style is that all specializations are defined inside base struct.
// However, here it is most likely impossible to implement without explicit full specialization for 0.
// This is because the recursive template specialization would not terminate for 0.
template<>
struct int_to_symbols<0> {
	using array = typename_array<value_wrapper<'0'>>;
};

#endif // TYPENAME_ARRAY_INT_TO_SYMBOLS_H