#include "myclib.h"
#include <string.h>
#include <stdint.h>
#include "emmintrin.h"
#include "immintrin.h"

uint64_t count_byte_doubles(char * str, uint64_t size) {
    uint64_t count = 0;
    while(size>16){
        __m128i first = _mm_lddqu_si128((__m128i*)(str));
        __m128i second = _mm_lddqu_si128((__m128i*)(str+1));
        __m128i mask = _mm_cmpistrm(first, second, _SIDD_CMP_EQUAL_EACH | _SIDD_UBYTE_OPS);
        count += _mm_popcnt_u64(mask[0]);
        str+=16;
        size-=16;
    }
    while (--size) {
        if (str[0] == str[1]) count++;
        str++;
    }
    return count;
}
