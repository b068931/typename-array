#ifndef TYPENAME_ARRAY_LEFT_TO_RIGHT_H
#define TYPENAME_ARRAY_LEFT_TO_RIGHT_H

#include "base.h"

template<typename array>
struct left_to_right {
private:
	template<typename_array_size_type counter, typename helper_array>
	struct left_to_right_helper {
		using new_array = helper_array;
	};

	template<typename_array_size_type counter, template<typename, typename...> class array_template, typename val, typename... other>
	struct left_to_right_helper<counter, array_template<val, other...>> {
		using new_array = typename combine<typename left_to_right_helper<counter - 1, typename_array<other...>>::new_array, typename_array<val>>::new_array;
	};

public:
	using new_array = typename left_to_right_helper<array::size, array>::new_array;
};

#endif // TYPENAME_ARRAY_LEFT_TO_RIGHT_H