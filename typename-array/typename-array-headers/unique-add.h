#ifndef TYPENAME_ARRAY_UNIQUE_ADD_H
#define TYPENAME_ARRAY_UNIQUE_ADD_H

#include "base.h"
#include "insert.h"
#include "find.h"

template<typename_array_size_t index, typename array, typename new_val>
struct unique_add {
private:
	template<typename_array_size_t found, typename helper_array, typename helper_new_val>
	struct unique_add_helper {
		using value = helper_array;
	};

	template<typename helper_array, typename helper_new_val>
	struct unique_add_helper<npos, helper_array, helper_new_val> {
		using value = typename insert<index, helper_array, helper_new_val>::new_array;
	};

public:
	using new_array = typename unique_add_helper<find<array, new_val>::index, array, new_val>::value;
};


#endif // TYPENAME_ARRAY_UNIQUE_ADD_H