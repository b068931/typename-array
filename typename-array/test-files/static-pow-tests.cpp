#include "../typename-array-primitives/static-pow.hpp"

int main() {
    // Test base cases
    static_assert(static_pow<5, 0>::result == 1, 
                  "Test failed: " "\"Any number raised to power 0 should be 1\"");
    static_assert(static_pow<10, 1>::result == 10, 
                  "Test failed: " "\"Any number raised to power 1 should equal the number itself\"");
    
    // Test positive base with various exponents
    static_assert(static_pow<2, 3>::result == 8, 
                  "Test failed: " "\"2^3 should equal 8\"");
    static_assert(static_pow<3, 4>::result == 81, 
                  "Test failed: " "\"3^4 should equal 81\"");
    static_assert(static_pow<10, 2>::result == 100, 
                  "Test failed: " "\"10^2 should equal 100\"");
    
    // Test with different bases and exponents
    static_assert(static_pow<1, 100>::result == 1, 
                  "Test failed: " "\"1^100 should equal 1\"");
    static_assert(static_pow<2, 8>::result == 256, 
                  "Test failed: " "\"2^8 should equal 256\"");
    static_assert(static_pow<3, 3>::result == 27, 
                  "Test failed: " "\"3^3 should equal 27\"");
    
    // Test with larger values
    static_assert(static_pow<2, 10>::result == 1024, 
                  "Test failed: " "\"2^10 should equal 1024\"");
    
    // Test zero as base with non-zero exponent
    static_assert(static_pow<0, 5>::result == 0, 
                  "Test failed: " "\"0^5 should equal 0\"");
    
    // Test zero as base with zero exponent
    static_assert(static_pow<0, 0>::result == 1, 
                  "Test failed: " "\"0^0 should equal 1 by convention\"");

    return 0;
}