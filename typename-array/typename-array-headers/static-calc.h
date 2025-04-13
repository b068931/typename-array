#ifndef TYPENAME_ARRAY_STATIC_CALC_H
#define TYPENAME_ARRAY_STATIC_CALC_H

#include "base.h"
#include "value.h"
#include "cut.h"
#include "find-one-of.h"
#include "left-to-right.h"
#include "find-priority.h"
#include "symbols-to-int.h"
#include "get.h"
#include "int-to-symbols.h"
#include "replace-part.h"
#include "typename-binder.h"

template<typename... symbols>
struct static_calc {
private:
	using expressions_symbols = typename_array<value<'('>, value<'%'>, value<'/'>, value<'*'>, value<'+'>, value<'-'>, value<')'>>;
	enum class expr_type {
		regular_expression,
		parentheses
	};

	template<typename array, typename_array_size_t start_index>
	struct find_last_closed_parentheses {
	private:
		template<typename helper_array, typename_array_size_t parentheses_count, typename_array_size_t index>
		struct find_last_closed_parentheses_helper {
			static constexpr typename_array_size_t indx = index;
		};

		template<template<typename, typename...> class templ, typename... other, typename_array_size_t parentheses_count, typename_array_size_t index, char character>
		struct find_last_closed_parentheses_helper<templ<value<character>, other...>, parentheses_count, index> {
            static constexpr typename_array_size_t parentheses_count_new = 
				(character == '(')
		            ? (parentheses_count + 1)
		            : (character == ')') ? (parentheses_count - 1) : parentheses_count;

			static constexpr typename_array_size_t indx = (parentheses_count == 0) ? index : find_last_closed_parentheses_helper<templ<other...>, parentheses_count_new, (index + 1)>::indx;
		};

	public:
		static constexpr typename_array_size_t index = find_last_closed_parentheses_helper<array, 1, start_index>::indx;
	};

	template<char sym, typename array, typename_array_size_t index>
	struct find_boundaries {
		using right_half_of_expression = typename cut<(index + 1), (array::size - 1), array>::new_array;
		static constexpr typename_array_size_t right_half_end = find_one_of<right_half_of_expression, expressions_symbols>::index;
		using true_right_half_end_type =
        std::conditional_t<(right_half_end == -1),
                         value<(array::size - 1)>,
                         value<(index + right_half_end)>>;
		static constexpr typename_array_size_t true_right_half_end = true_right_half_end_type::get_value;

		using left_half_of_expression = typename left_to_right<typename cut<0, (index - 1), array>::new_array>::new_array;
		static constexpr typename_array_size_t left_half_end = find_one_of<left_half_of_expression, expressions_symbols>::index;
		using true_left_half_end_type =
        std::conditional_t<(left_half_end == -1),
                         value<static_cast<typename_array_size_t>(0)>,
                         value<index - left_half_end>>;
		static constexpr typename_array_size_t true_left_half_end = true_left_half_end_type::get_value;

		using expression_boundaries = typename_array<
			value<expr_type::regular_expression>,
			value<true_left_half_end>,
			value<true_right_half_end>,
			value<index>>;
	};

	template<typename array, typename_array_size_t index>
	struct find_boundaries<'(', array, index> {
		using right_half_of_expression = typename cut<(index + 1), (array::size - 1), array>::new_array;
		static constexpr typename_array_size_t last_closed_parentheses = find_last_closed_parentheses<right_half_of_expression, index>::index;

		using expression_boundaries = typename_array<
			value<expr_type::parentheses>,
			value<index>,
			value<last_closed_parentheses>,
			value<index>>;
	};

	template<typename... helper_symbols>
	struct find_expression_with_highest_priority {
		static constexpr typename_array_size_t highest_priority_symbol = find_priority<typename_array<helper_symbols...>, expressions_symbols>::index;

		using symbol = typename get<highest_priority_symbol, typename_array<helper_symbols...>>::value;
		using array = typename combine<
			typename find_boundaries<symbol::get_value, typename_array<helper_symbols...>, highest_priority_symbol>::expression_boundaries, typename_array<symbol>>::new_array;
	};

	template<expr_type ex_type, typename simple_expression_info, typename array>
	struct calculate_simple_expression {
	private:
		template<char symbol, typename left_part, typename right_part>
		struct calc;

		template<typename left_part, typename right_part>
		struct calc<'%', left_part, right_part> {
			static constexpr typename_array_size_t value = left_part::template acquire<symbols_to_int>::value % right_part::template acquire<symbols_to_int>::value;
		};

		template<typename left_part, typename right_part>
		struct calc<'*', left_part, right_part> {
			static constexpr typename_array_size_t value = left_part::template acquire<symbols_to_int>::value * right_part::template acquire<symbols_to_int>::value;
		};

		template<typename left_part, typename right_part>
		struct calc<'/', left_part, right_part> {
			static constexpr typename_array_size_t value = left_part::template acquire<symbols_to_int>::value / right_part::template acquire<symbols_to_int>::value;
		};

		template<typename left_part, typename right_part>
		struct calc<'+', left_part, right_part> {
			static constexpr typename_array_size_t value = left_part::template acquire<symbols_to_int>::value + right_part::template acquire<symbols_to_int>::value;
		};

		template<typename left_part, typename right_part>
		struct calc<'-', left_part, right_part> {
			static constexpr typename_array_size_t value = left_part::template acquire<symbols_to_int>::value - right_part::template acquire<symbols_to_int>::value;
		};

	public:
		using start_type = typename get<1, simple_expression_info>::value;
		using end_type = typename get<2, simple_expression_info>::value;
		using expr_index = typename get<3, simple_expression_info>::value;
		using expr_sym_type = typename get<4, simple_expression_info>::value;

		using calc_symbols = typename int_to_symbols<calc<expr_sym_type::get_value,
			typename cut<start_type::get_value, (expr_index::get_value - 1), array>::new_array,
			typename cut<(expr_index::get_value + 1), end_type::get_value, array>::new_array>::value
		>::array;
	};

	template<typename is_changeable, typename... helper_symbols>
	struct static_calc_helper {
		using array = typename_array<helper_symbols...>;
		using simple_expression_info = typename find_expression_with_highest_priority<helper_symbols...>::array;

		using expr_type = typename get<0, simple_expression_info>::value;
		using start_type = typename get<1, simple_expression_info>::value;
		using end_type = typename get<2, simple_expression_info>::value;

		using new_symbols = typename calculate_simple_expression<expr_type::get_value, simple_expression_info, array>::calc_symbols;
		using new_array = typename replace_part<array, start_type::get_value, end_type::get_value, new_symbols>::new_array;

		using binder = typename_binder<static_calc_helper, value<(find_one_of<new_array, expressions_symbols>::index != -1)>>;
		static constexpr typename_array_size_t value = new_array::template acquire<binder::template bind>::value;
	};

	template<typename... helper_symbols>
	struct static_calc_helper<value<false>, helper_symbols...> {
		static constexpr typename_array_size_t value = symbols_to_int<helper_symbols...>::value;
	};

	template<typename simple_expression_info, typename array>
	struct calculate_simple_expression<expr_type::parentheses, simple_expression_info, array> {
		using start_type = typename get<1, simple_expression_info>::value;
		using end_type = typename get<2, simple_expression_info>::value;

		using in_parentheses = typename cut<(start_type::get_value + 1), (end_type::get_value - 1), array>::new_array;
		using binder = typename_binder<static_calc_helper, value<(find_one_of<in_parentheses, expressions_symbols>::index != -1)>>;
		using calc_symbols = typename int_to_symbols<in_parentheses::template acquire<binder::template bind>::value>::array;
	};

public:
	static constexpr typename_array_size_t result = static_calc_helper<value<(find_one_of<typename_array<symbols...>, expressions_symbols>::index != -1)>, symbols...>::value;
};

#endif // TYPENAME_ARRAY_STATIC_CALC_H