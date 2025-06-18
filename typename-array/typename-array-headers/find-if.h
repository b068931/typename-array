#ifndef TYPENAME_ARRAY_FIND_IF_H
#define TYPENAME_ARRAY_FIND_IF_H

#include "base.h"

template<typename array, template<typename> class predicate>
struct find_if {
private:
	template<typename_array_size_type index, bool found, typename helper_array>
	struct find_if_helper {
		static constexpr typename_array_size_type indx = npos;
	};

	template<typename_array_size_type index, bool found, typename val, typename... other, template<typename, typename...> class templ>
	struct find_if_helper<index, found, templ<val, other...>> {
		static constexpr typename_array_size_type indx = find_if_helper<index + 1, predicate<val>::value, templ<other...>>::ind;
	};

	template<typename_array_size_type index, typename... other, template<typename, typename...> class templ>
	struct find_if_helper<index, true, templ<other...>> {
		static constexpr typename_array_size_type indx = index - 1;
	};

public:
	static constexpr typename_array_size_type index = find_if_helper<0, false, array>::indx;
};

#endif // TYPENAME_ARRAY_FIND_IF_H