#ifndef TYPENAME_ARRAY_SORT_H
#define TYPENAME_ARRAY_SORT_H

#include "base.h"
#include "get.h"
#include "cut.h"

template<typename array, template<typename, typename> class predicate>
struct sort {
public:
	template<typename arr_1, typename arr_2>
	struct combine_sorted_arrays;

	template<typename other, typename val_1, typename... other_1, template<typename, typename...> class templ>
	struct combine_sorted_arrays<templ<val_1, other_1...>, other> {
		using new_array = templ<val_1, other_1...>;
	};

	template<typename other, typename val_2, typename... other_2, template<typename, typename...> class templ>
	struct combine_sorted_arrays<other, templ<val_2, other_2...>> {
		using new_array = templ<val_2, other_2...>;
	};

	template<typename val_1, typename... other_1, typename val_2, typename... other_2, template<typename, typename...> class templ>
	struct combine_sorted_arrays<templ<val_1, other_1...>, templ<val_2, other_2...>> {
		static constexpr bool is_value_before = predicate<val_1, val_2>::value;

		using first_val = typename std::conditional<is_value_before, val_1, val_2>::type;
		using arrs = typename std::conditional<
			is_value_before,
			templ<templ<other_1...>, templ<val_2, other_2...>>,
			templ<templ<val_1, other_1...>, templ<other_2...>>
		>::type;

		using new_array = typename combine<templ<first_val>,
			typename combine_sorted_arrays<typename get<0, arrs>::value, typename get<1, arrs>::value>::new_array
		>::new_array;
	};

	template<typename first, typename second>
	struct sort_help {
		using new_array = typename_array<>;
	};

	template<typename first, typename val, typename... other, template<typename, typename...> class templ>
	struct sort_help<first, templ<val, other...>> {
		using new_array = templ<val, other...>;
	};

	template<typename second, typename val, typename... other, template<typename, typename...> class templ>
	struct sort_help<templ<val, other...>, second> {
		using new_array = templ<val, other...>;
	};

	template<typename other_1, typename other_2, template<typename> class templ>
	struct sort_help<templ<other_1>, templ<other_2>> {
		using array_1 = templ<other_1>;
		using array_2 = templ<other_2>;

		using new_array = typename combine_sorted_arrays<array_1, array_2>::new_array;
	};

	template<typename val_1, typename val_2, typename... other_1, typename... other_2, template<typename, typename...> class templ>
	struct sort_help<templ<val_1, other_1...>, templ<val_2, other_2...>> {
		using array_1 = templ<val_1, other_1...>;
		using array_2 = templ<val_2, other_2...>;

		static constexpr typename_array_size_t first = array_1::size / 2;
		static constexpr typename_array_size_t second = array_2::size / 2;

		using first_half = typename sort_help<typename cut<0, first - 1, array_1>::new_array, typename cut<first, array_1::size - 1, array_1>::new_array>::new_array;
		using second_half = typename sort_help<typename cut<0, second - 1, array_2>::new_array, typename cut<second, array_2::size - 1, array_2>::new_array>::new_array;

		using new_array = typename combine_sorted_arrays<first_half, second_half>::new_array;
	};

	static constexpr typename_array_size_t half = array::size / 2;

public:
	using new_array = typename sort_help<typename cut<0, half - 1, array>::new_array, typename cut<half, array::size - 1, array>::new_array>::new_array;
};


#endif // TYPENAME_ARRAY_SORT_H