#ifndef TYPENAME_ARRAY_REPLACE_PART_H
#define TYPENAME_ARRAY_REPLACE_PART_H

#include "base.h"
#include "cut.h"

template<typename array, typename_array_size_t start, typename_array_size_t end, typename to_place>
struct replace_part {
	using new_array = typename combine<
		typename combine<typename cut<0, (start - 1), array>::new_array, to_place>::new_array,
		typename cut<end + 1, array::size - 1, array>::new_array>::new_array;
};

#endif // TYPENAME_ARRAY_REPLACE_PART_H