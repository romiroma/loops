#include <stdint.h>
#include <immintrin.h>

void test_c_simd(uint16_t *buf, const uint16_t size, uint64_t *sum) {
    __m256i sum64 = _mm256_setzero_si256(); // Initialize 256-bit vector to zero
    __m256i zero = _mm256_setzero_si256(); // Zero vector for unpacking

    const uint16_t *end = buf + (size & ~15); // Process in chunks of 16 elements
    while (buf < end) {
        __m256i data = _mm256_loadu_si256((__m256i *)buf); // Load 16 uint16_t values
        __m256i data_lo = _mm256_unpacklo_epi16(data, zero); // Unpack lower 8 uint16_t to uint32_t
        __m256i data_hi = _mm256_unpackhi_epi16(data, zero); // Unpack higher 8 uint16_t to uint32_t

        __m256i sum_lo = _mm256_add_epi32(data_lo, _mm256_unpacklo_epi32(sum64, zero));
        __m256i sum_hi = _mm256_add_epi32(data_hi, _mm256_unpackhi_epi32(sum64, zero));

        // Horizontal sum of the 256-bit vector
        __m256i sum32 = _mm256_add_epi32(sum_lo, sum_hi);
        __m128i sum128 = _mm_add_epi32(_mm256_castsi256_si128(sum32), _mm256_extracti128_si256(sum32, 1));
        sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(2, 3, 0, 1)));
        sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(1, 0, 3, 2)));
        *sum += _mm_cvtsi128_si32(sum128); // Add the final sum to the result
        buf += 16;
    }

    // Process remaining elements
    end = buf + (size & 15);
    while (buf < end) {
        *sum += *buf;
        buf++;
    }
}