#include <iostream>
#include "../typename-array-primitives/static-calculator.hpp"

int main() {
    // Test basic arithmetic operations
    using addition_expr = typename_array<value_wrapper<'1'>, value_wrapper<'+'>, value_wrapper<'2'>>;
    static_assert(addition_expr::template acquire<static_calculator>::result == 3,
                  "Test failed: Basic addition should evaluate to 3");
    std::cout << "Basic addition (1+2): " << addition_expr::template acquire<static_calculator>::result << std::endl;

    using subtraction_expr = typename_array<value_wrapper<'5'>, value_wrapper<'-'>, value_wrapper<'2'>>;
    static_assert(subtraction_expr::template acquire<static_calculator>::result == 3,
                  "Test failed: Basic subtraction should evaluate to 3");
    std::cout << "Basic subtraction (5-2): " << subtraction_expr::template acquire<static_calculator>::result << std::endl;

    using multiplication_expr = typename_array<value_wrapper<'3'>, value_wrapper<'*'>, value_wrapper<'4'>>;
    static_assert(multiplication_expr::template acquire<static_calculator>::result == 12,
                  "Test failed: Basic multiplication should evaluate to 12");
    std::cout << "Basic multiplication (3*4): " << multiplication_expr::template acquire<static_calculator>::result << std::endl;

    using division_expr = typename_array<value_wrapper<'8'>, value_wrapper<'/'>, value_wrapper<'2'>>;
    static_assert(division_expr::template acquire<static_calculator>::result == 4,
                  "Test failed: Basic division should evaluate to 4");
    std::cout << "Basic division (8/2): " << division_expr::template acquire<static_calculator>::result << std::endl;

    using modulo_expr = typename_array<value_wrapper<'7'>, value_wrapper<'%'>, value_wrapper<'3'>>;
    static_assert(modulo_expr::template acquire<static_calculator>::result == 1,
                  "Test failed: Basic modulo should evaluate to 1");
    std::cout << "Basic modulo (7%3): " << modulo_expr::template acquire<static_calculator>::result << std::endl;

    // Test order of operations
    using order_expr1 = typename_array<value_wrapper<'2'>, value_wrapper<'+'>, value_wrapper<'3'>, value_wrapper<'*'>, value_wrapper<'4'>>;
    static_assert(order_expr1::template acquire<static_calculator>::result == 14,
                  "Test failed: Expression with proper order of operations should evaluate to 14");
    std::cout << "Order of operations (2+3*4): " << order_expr1::template acquire<static_calculator>::result << std::endl;

    using order_expr2 = typename_array<value_wrapper<'8'>, value_wrapper<'/'>, value_wrapper<'4'>, value_wrapper<'+'>, value_wrapper<'3'>>;
    static_assert(order_expr2::template acquire<static_calculator>::result == 5,
                  "Test failed: Division and addition should evaluate to 5");
    std::cout << "Division and addition (8/4+3): " << order_expr2::template acquire<static_calculator>::result << std::endl;

    // Test parentheses
    using paren_expr1 = typename_array<value_wrapper<'('>, value_wrapper<'2'>, value_wrapper<'+'>, value_wrapper<'3'>, value_wrapper<')'>, value_wrapper<'*'>, value_wrapper<'4'>>;
    static_assert(paren_expr1::template acquire<static_calculator>::result == 20,
                  "Test failed: Expression with parentheses should evaluate to 20");
    std::cout << "Expression with parentheses ((2+3)*4): " << paren_expr1::template acquire<static_calculator>::result << std::endl;

    using paren_expr2 = typename_array<value_wrapper<'2'>, value_wrapper<'*'>, value_wrapper<'('>, value_wrapper<'3'>, value_wrapper<'+'>, value_wrapper<'4'>, value_wrapper<')'>>;
    static_assert(paren_expr2::template acquire<static_calculator>::result == 14,
                  "Test failed: Expression with parentheses should evaluate to 14");
    std::cout << "Expression with parentheses (2*(3+4)): " << paren_expr2::template acquire<static_calculator>::result << std::endl;

    // Test multi-digit numbers
    using multi_digit_expr = typename_array<value_wrapper<'1'>, value_wrapper<'2'>, value_wrapper<'3'>, value_wrapper<'+'>, value_wrapper<'4'>, value_wrapper<'5'>, value_wrapper<'6'>>;
    static_assert(multi_digit_expr::template acquire<static_calculator>::result == 579,
                  "Test failed: Expression with multi-digit numbers should evaluate to 579");
    std::cout << "Multi-digit numbers (123+456): " << multi_digit_expr::template acquire<static_calculator>::result << std::endl;

    // Test complex expressions
    using complex_expr1 = typename_array<value_wrapper<'2'>, value_wrapper<'*'>, value_wrapper<'('>, value_wrapper<'3'>, value_wrapper<'+'>, value_wrapper<'4'>, value_wrapper<')'>, value_wrapper<'-'>, value_wrapper<'5'>, value_wrapper<'/'>, value_wrapper<'2'>>;
    static_assert(complex_expr1::template acquire<static_calculator>::result == 12,
                  "Test failed: Complex expression should evaluate to 12");
    std::cout << "Complex expression (2*(3+4)-5/2): " << complex_expr1::template acquire<static_calculator>::result << std::endl;

    using complex_expr2 = typename_array<value_wrapper<'('>, value_wrapper<'1'>, value_wrapper<'0'>, value_wrapper<'+'>, value_wrapper<'5'>, value_wrapper<'*'>, value_wrapper<'2'>, value_wrapper<')'>, value_wrapper<'/'>, value_wrapper<'('>, value_wrapper<'4'>, value_wrapper<'-'>, value_wrapper<'2'>, value_wrapper<')'>>;
    static_assert(complex_expr2::template acquire<static_calculator>::result == 10,
                  "Test failed: Complex expression with nested parentheses should evaluate to 10");
    std::cout << "Complex expression with nested parentheses ((10+5*2)/(4-2)): " << complex_expr2::template acquire<static_calculator>::result << std::endl;

    // Test multiple nested parentheses
    using nested_paren_expr = typename_array<
        value_wrapper<'('>, value_wrapper<'1'>, value_wrapper<'+'>, 
        value_wrapper<'('>, value_wrapper<'('>, value_wrapper<'2'>, value_wrapper<'+'>, value_wrapper<'3'>, value_wrapper<')'>, 
        value_wrapper<'*'>, 
        value_wrapper<'('>, value_wrapper<'4'>, value_wrapper<'+'>, value_wrapper<'5'>, value_wrapper<')'>, value_wrapper<')'>, 
        value_wrapper<')'>
    >;
    static_assert(nested_paren_expr::template acquire<static_calculator>::result == 46,
                  "Test failed: Expression with multiple nested parentheses should evaluate to 46");
    std::cout << "Multiple nested parentheses (1+((2+3)*(4+5))): " << nested_paren_expr::template acquire<static_calculator>::result << std::endl;

    return 0;
}