#ifndef TYPENAME_ARRAY_STATIC_POW_H
#define TYPENAME_ARRAY_STATIC_POW_H

#include "base.h"

template<typename_array_size_type value, typename_array_size_type counter>
struct static_pow {
private:
    template<typename_array_size_type val, typename_array_size_type n>
    struct static_pow_helper {
        static_assert(n > 0, "Exponent must be greater than 0.");
        static constexpr typename_array_size_type result = val * static_pow<val, (n - 1)>::result;
    };

    template<typename_array_size_type val>
    struct static_pow_helper<val, 0> {
        static constexpr typename_array_size_type result = 1;
    };

public:
    static constexpr typename_array_size_type result = static_pow_helper<value, counter>::result;
};

#endif // TYPENAME_ARRAY_STATIC_POW_H