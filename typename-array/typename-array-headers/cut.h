#ifndef TYPENAME_ARRAY_CUT_H
#define TYPENAME_ARRAY_CUT_H

#include "base.h"

template<typename_array_size_type start, typename_array_size_type end, typename array>
struct cut {
private:
	template<bool use, typename_array_size_type index, typename helper_array>
	struct cut_helper {
		using new_array = typename_array<>;
	};

	template<bool use, typename_array_size_type index, typename val, typename... other, template<typename, typename...> class templ>
	struct cut_helper<use, index, templ<val, other...>> {
		static constexpr typename_array_size_type next_index = index + 1;
		using new_array = typename cut_helper<((next_index >= start) && (next_index <= end)), next_index, templ<other...>>::new_array;
	};

	template<typename_array_size_type index, typename val, typename... other, template<typename, typename...> class templ>
	struct cut_helper<true, index, templ<val, other...>> {
		static constexpr typename_array_size_type next_index = index + 1;
		using new_array = typename combine<templ<val>, typename cut_helper<((next_index >= start) && (next_index <= end)), next_index, templ<other...>>::new_array>::new_array;
	};

public:
	using new_array = typename cut_helper<(start == 0) && (end >= start) && (end < array::size), 0, array>::new_array;
};

#endif // TYPENAME_ARRAY_CUT_H