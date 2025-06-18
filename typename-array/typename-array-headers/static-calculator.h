#ifndef TYPENAME_ARRAY_STATIC_CALC_H
#define TYPENAME_ARRAY_STATIC_CALC_H

#include "base.h"
#include "value_wrapper.h"
#include "cut.h"
#include "find-one-of.h"
#include "left-to-right.h"
#include "find-priority.h"
#include "symbols-to-int.h"
#include "get.h"
#include "int-to-symbols.h"
#include "replace-part.h"
#include "typename-binder.h"

/// <summary>
/// Compiles and evaluates a mathematical expression at compile time using type-level computation.
/// Supports basic arithmetic operations (+, -, *, /, %) and parentheses.
/// </summary>
/// <typeparam name="symbols">A sequence of value types representing the characters in the expression.</typeparam>
template<typename... symbols>
struct static_calculator {
private:
    /// <summary>
    /// Array of recognized operators and parentheses that can appear in expressions.
    /// </summary>
    using expressions_symbols = typename_array<value_wrapper<'('>, value_wrapper<'%'>, value_wrapper<'/'>, value_wrapper<'*'>, value_wrapper<'+'>, value_wrapper<'-'>, value_wrapper<')'>>;
    
    /// <summary>
    /// Enumeration of expression types to differentiate between regular expressions and parenthesized expressions.
    /// </summary>
    enum class expression_type {
        regular_expression,
        parentheses
    };

    /// <summary>
    /// Finds the matching closing parenthesis for an opening parenthesis.
    /// </summary>
    /// <typeparam name="array">The array containing the expression.</typeparam>
    /// <typeparam name="start_index">The index of the opening parenthesis.</typeparam>
    template<typename array, typename_array_size_type start_index>
    struct find_last_closed_parentheses {
    private:
        /// <summary>
        /// Helper structure that tracks parenthesis nesting to find the matching closing parenthesis.
        /// </summary>
        /// <typeparam name="helper_array">The remaining portion of the array being processed.</typeparam>
        /// <typeparam name="parentheses_count">Current nesting level of parentheses.</typeparam>
        /// <typeparam name="index">Current position being examined.</typeparam>
        template<typename helper_array, typename_array_size_type parentheses_count, typename_array_size_type index>
        struct find_last_closed_parentheses_helper {
            /// <summary>
            /// The index where the search terminates.
            /// </summary>
            static constexpr typename_array_size_type indx = index;
        };

        /// <summary>
        /// Recursive helper that processes each character and tracks parenthesis nesting.
        /// </summary>
        template<template<typename, typename...> class templ, typename... other, typename_array_size_type parentheses_count, typename_array_size_type index, char character>
        struct find_last_closed_parentheses_helper<templ<value_wrapper<character>, other...>, parentheses_count, index> {
            /// <summary>
            /// Updates the parentheses count based on encountered parentheses.
            /// Increments for '(', decrements for ')', otherwise no change.
            /// </summary>
            static constexpr typename_array_size_type parentheses_count_new = 
                (character == '(')
                    ? (parentheses_count + 1)
                    : (character == ')') ? (parentheses_count - 1) : parentheses_count;

            /// <summary>
            /// The index of the matching closing parenthesis, or continues the search.
            /// Returns the current index if parentheses_count becomes zero (matching parenthesis found).
            /// </summary>
            static constexpr typename_array_size_type indx = (parentheses_count == 0) ? index : find_last_closed_parentheses_helper<templ<other...>, parentheses_count_new, (index + 1)>::indx;
        };

    public:
        /// <summary>
        /// The index of the closing parenthesis that matches the opening parenthesis at start_index.
        /// </summary>
        static constexpr typename_array_size_type index = find_last_closed_parentheses_helper<array, 1, start_index>::indx;
    };

    /// <summary>
    /// Determines the boundaries of an expression around an operator.
    /// For regular expressions, finds the complete left and right operands.
    /// </summary>
    /// <typeparam name="sym">The operator character.</typeparam>
    /// <typeparam name="array">The array containing the expression.</typeparam>
    /// <typeparam name="index">The index of the operator.</typeparam>
    template<char sym, typename array, typename_array_size_type index>
    struct find_boundaries {
        /// <summary>
        /// The right half of the expression after the operator.
        /// </summary>
        using right_half_of_expression = typename cut<(index + 1), (array::size - 1), array>::new_array;
        
        /// <summary>
        /// The index of the next operator in the right half, or -1 if none exists.
        /// </summary>
        static constexpr typename_array_size_type right_half_end = find_one_of<right_half_of_expression, expressions_symbols>::index;
        
        /// <summary>
        /// Type representing the true end index of the right operand.
        /// If no more operators are found, uses the end of the array.
        /// </summary>
        using true_right_half_end_type =
        std::conditional_t<(right_half_end == -1),
                         value_wrapper<(array::size - 1)>,
                         value_wrapper<(index + right_half_end)>>;
                         
        /// <summary>
        /// The end index of the right operand.
        /// </summary>
        static constexpr typename_array_size_type true_right_half_end = true_right_half_end_type::get_value;

        /// <summary>
        /// The left half of the expression before the operator, reversed for search.
        /// </summary>
        using left_half_of_expression = typename left_to_right<typename cut<0, (index - 1), array>::new_array>::new_array;
        
        /// <summary>
        /// The index of the previous operator in the left half, or -1 if none exists.
        /// </summary>
        static constexpr typename_array_size_type left_half_end = find_one_of<left_half_of_expression, expressions_symbols>::index;
        
        /// <summary>
        /// Type representing the true start index of the left operand.
        /// If no previous operators are found, uses the start of the array.
        /// </summary>
        using true_left_half_end_type =
        std::conditional_t<(left_half_end == -1),
                         value_wrapper<static_cast<typename_array_size_type>(0)>,
                         value_wrapper<index - left_half_end>>;
                         
        /// <summary>
        /// The start index of the left operand.
        /// </summary>
        static constexpr typename_array_size_type true_left_half_end = true_left_half_end_type::get_value;

        /// <summary>
        /// Array containing information about the expression boundaries:
        /// [expression type, left boundary, right boundary, operator index]
        /// </summary>
        using expression_boundaries = typename_array<
            value_wrapper<expression_type::regular_expression>,
            value_wrapper<true_left_half_end>,
            value_wrapper<true_right_half_end>,
            value_wrapper<index>>;
    };

    /// <summary>
    /// Specialization for parenthesized expressions, which have different boundary rules.
    /// </summary>
    /// <typeparam name="array">The array containing the expression.</typeparam>
    /// <typeparam name="index">The index of the opening parenthesis.</typeparam>
    template<typename array, typename_array_size_type index>
    struct find_boundaries<'(', array, index> {
        /// <summary>
        /// The right half of the expression after the opening parenthesis.
        /// </summary>
        using right_half_of_expression = typename cut<(index + 1), (array::size - 1), array>::new_array;
        
        /// <summary>
        /// The index of the matching closing parenthesis.
        /// </summary>
        static constexpr typename_array_size_type last_closed_parentheses = find_last_closed_parentheses<right_half_of_expression, index>::index;

        /// <summary>
        /// Array containing information about the parenthesized expression boundaries:
        /// [expression type, opening parenthesis index, closing parenthesis index, opening parenthesis index]
        /// </summary>
        using expression_boundaries = typename_array<
            value_wrapper<expression_type::parentheses>,
            value_wrapper<index>,
            value_wrapper<last_closed_parentheses>,
            value_wrapper<index>>;
    };

    /// <summary>
    /// Finds the expression with the highest operator precedence to evaluate next.
    /// </summary>
    /// <typeparam name="helper_symbols">The symbols in the expression.</typeparam>
    template<typename... helper_symbols>
    struct find_expression_with_highest_priority {
        /// <summary>
        /// The index of the highest priority operator in the expression.
        /// </summary>
        static constexpr typename_array_size_type highest_priority_symbol = find_priority<typename_array<helper_symbols...>, expressions_symbols>::index;

        /// <summary>
        /// The type of the highest priority operator.
        /// </summary>
        using symbol = typename get<highest_priority_symbol, typename_array<helper_symbols...>>::value;
        
        /// <summary>
        /// Array containing the expression boundaries and the operator symbol.
        /// </summary>
        using array = typename combine<
            typename find_boundaries<symbol::get_value, typename_array<helper_symbols...>, highest_priority_symbol>::expression_boundaries, typename_array<symbol>>::new_array;
    };

    /// <summary>
    /// Calculates the result of a simple (atomic) expression based on its type and operands.
    /// </summary>
    /// <typeparam name="ex_type">The type of the expression (regular or parenthesized).</typeparam>
    /// <typeparam name="simple_expression_info">Information about the expression boundaries.</typeparam>
    /// <typeparam name="array">The array containing the expression.</typeparam>
    template<expression_type ex_type, typename simple_expression_info, typename array>
    struct calculate_simple_expression {
    private:
        /// <summary>
        /// Helper structure for performing different calculations based on operator.
        /// </summary>
        /// <typeparam name="symbol">The operator character.</typeparam>
        /// <typeparam name="left_part">The left operand.</typeparam>
        /// <typeparam name="right_part">The right operand.</typeparam>
        template<char symbol, typename left_part, typename right_part>
        struct calc;

        /// <summary>
        /// Specialization for the modulo operator (%).
        /// </summary>
        template<typename left_part, typename right_part>
        struct calc<'%', left_part, right_part> {
            /// <summary>
            /// The result of the modulo operation.
            /// </summary>
            static constexpr typename_array_size_type value = left_part::template acquire<symbols_to_int>::result % right_part::template acquire<symbols_to_int>::result;
        };

        /// <summary>
        /// Specialization for the multiplication operator (*).
        /// </summary>
        template<typename left_part, typename right_part>
        struct calc<'*', left_part, right_part> {
            /// <summary>
            /// The result of the multiplication operation.
            /// </summary>
            static constexpr typename_array_size_type value = left_part::template acquire<symbols_to_int>::result * right_part::template acquire<symbols_to_int>::result;
        };

        /// <summary>
        /// Specialization for the division operator (/).
        /// </summary>
        template<typename left_part, typename right_part>
        struct calc<'/', left_part, right_part> {
            /// <summary>
            /// The result of the division operation.
            /// </summary>
            static constexpr typename_array_size_type value = left_part::template acquire<symbols_to_int>::result / right_part::template acquire<symbols_to_int>::result;
        };

        /// <summary>
        /// Specialization for the addition operator (+).
        /// </summary>
        template<typename left_part, typename right_part>
        struct calc<'+', left_part, right_part> {
            /// <summary>
            /// The result of the addition operation.
            /// </summary>
            static constexpr typename_array_size_type value = left_part::template acquire<symbols_to_int>::result + right_part::template acquire<symbols_to_int>::result;
        };

        /// <summary>
        /// Specialization for the subtraction operator (-).
        /// </summary>
        template<typename left_part, typename right_part>
        struct calc<'-', left_part, right_part> {
            /// <summary>
            /// The result of the subtraction operation.
            /// </summary>
            static constexpr typename_array_size_type value = left_part::template acquire<symbols_to_int>::result - right_part::template acquire<symbols_to_int>::result;
        };

    public:
        /// <summary>
        /// The start index of the expression.
        /// </summary>
        using start_type = typename get<1, simple_expression_info>::value;
        
        /// <summary>
        /// The end index of the expression.
        /// </summary>
        using end_type = typename get<2, simple_expression_info>::value;
        
        /// <summary>
        /// The index of the operator.
        /// </summary>
        using expr_index = typename get<3, simple_expression_info>::value;
        
        /// <summary>
        /// The operator symbol.
        /// </summary>
        using expr_sym_type = typename get<4, simple_expression_info>::value;

        /// <summary>
        /// The result of the calculation converted back to a sequence of digit symbols.
        /// </summary>
        using calc_symbols = typename int_to_symbols<calc<expr_sym_type::get_value,
            typename cut<start_type::get_value, (expr_index::get_value - 1), array>::new_array,
            typename cut<(expr_index::get_value + 1), end_type::get_value, array>::new_array>::value
        >::array;
    };

    /// <summary>
    /// Main recursion helper for evaluating expressions.
    /// Continues recursion as long as operators remain in the expression.
    /// </summary>
    /// <typeparam name="is_changeable">Flag indicating if the expression still contains operators.</typeparam>
    /// <typeparam name="helper_symbols">The symbols in the expression.</typeparam>
    template<typename is_changeable, typename... helper_symbols>
    struct static_calculator_helper {
        /// <summary>
        /// The current expression as an array.
        /// </summary>
        using array = typename_array<helper_symbols...>;
        
        /// <summary>
        /// Information about the highest priority expression to evaluate next.
        /// </summary>
        using simple_expression_info = typename find_expression_with_highest_priority<helper_symbols...>::array;

        /// <summary>
        /// The type of the expression (regular or parenthesized).
        /// </summary>
        using expr_type = typename get<0, simple_expression_info>::value;
        
        /// <summary>
        /// The start index of the expression.
        /// </summary>
        using start_type = typename get<1, simple_expression_info>::value;
        
        /// <summary>
        /// The end index of the expression.
        /// </summary>
        using end_type = typename get<2, simple_expression_info>::value;

        /// <summary>
        /// The result symbols of calculating the current expression.
        /// </summary>
        using new_symbols = typename calculate_simple_expression<expr_type::get_value, simple_expression_info, array>::calc_symbols;
        
        /// <summary>
        /// The array with the calculated expression replaced.
        /// </summary>
        using new_array = typename replace_part<array, start_type::get_value, end_type::get_value, new_symbols>::new_array;

        /// <summary>
        /// Binder for continuing recursion if operators remain.
        /// </summary>
        using binder = typename_binder<static_calculator_helper, value_wrapper<(find_one_of<new_array, expressions_symbols>::index != -1)>>;
        
        /// <summary>
        /// The value of the expression after recursive evaluation.
        /// </summary>
        static constexpr typename_array_size_type value = new_array::template acquire<binder::template bind>::value;
    };

    /// <summary>
    /// Terminal case for recursion when no operators remain.
    /// Converts the remaining digit symbols to an integer.
    /// </summary>
    template<typename... helper_symbols>
    struct static_calculator_helper<value_wrapper<false>, helper_symbols...> {
        /// <summary>
        /// The final value of the expression.
        /// </summary>
        static constexpr typename_array_size_type value = symbols_to_int<helper_symbols...>::result;
    };

    /// <summary>
    /// Specialization for calculating parenthesized expressions.
    /// Handles the recursion into evaluating the expression inside parentheses.
    /// </summary>
    template<typename simple_expression_info, typename array>
    struct calculate_simple_expression<expression_type::parentheses, simple_expression_info, array> {
        /// <summary>
        /// The index of the opening parenthesis.
        /// </summary>
        using start_type = typename get<1, simple_expression_info>::value;
        
        /// <summary>
        /// The index of the closing parenthesis.
        /// </summary>
        using end_type = typename get<2, simple_expression_info>::value;

        /// <summary>
        /// The expression inside the parentheses.
        /// </summary>
        using in_parentheses = typename cut<(start_type::get_value + 1), (end_type::get_value - 1), array>::new_array;
        
        /// <summary>
        /// Binder for recursively evaluating the parenthesized expression.
        /// </summary>
        using binder = typename_binder<static_calculator_helper, value_wrapper<(find_one_of<in_parentheses, expressions_symbols>::index != -1)>>;
        
        /// <summary>
        /// The result of evaluating the parenthesized expression, converted to digit symbols.
        /// </summary>
        using calc_symbols = typename int_to_symbols<in_parentheses::template acquire<binder::template bind>::value>::array;
    };

public:
    /// <summary>
    /// The final result of evaluating the mathematical expression.
    /// </summary>
    static constexpr typename_array_size_type result = static_calculator_helper<value_wrapper<(find_one_of<typename_array<symbols...>, expressions_symbols>::index != -1)>, symbols...>::value;
};

#endif // TYPENAME_ARRAY_STATIC_CALC_H
