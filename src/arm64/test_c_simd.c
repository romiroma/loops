#include <stdint.h>
#include <arm_neon.h>

void test_c_simd(uint16_t *buf, const uint16_t size, uint64_t *sum) {
    uint32x4_t sum_vec = vdupq_n_u32(0); // Initialize 128-bit vector to zero

    const uint16_t *end = buf + (size & ~15); // Process in chunks of 16 elements
    while (buf < end) {
        uint16x8_t data1 = vld1q_u16(buf);       // Load first 8 uint16_t values
        uint16x8_t data2 = vld1q_u16(buf + 8);   // Load next 8 uint16_t values

        uint32x4_t data1_lo = vmovl_u16(vget_low_u16(data1));  // Unpack lower 4 uint16_t to uint32_t
        uint32x4_t data1_hi = vmovl_u16(vget_high_u16(data1)); // Unpack higher 4 uint16_t to uint32_t
        uint32x4_t data2_lo = vmovl_u16(vget_low_u16(data2));  // Unpack lower 4 uint16_t to uint32_t
        uint32x4_t data2_hi = vmovl_u16(vget_high_u16(data2)); // Unpack higher 4 uint16_t to uint32_t

        // Accumulate the sums
        sum_vec = vaddq_u32(sum_vec, data1_lo);
        sum_vec = vaddq_u32(sum_vec, data1_hi);
        sum_vec = vaddq_u32(sum_vec, data2_lo);
        sum_vec = vaddq_u32(sum_vec, data2_hi);

        buf += 16;
    }

    // Horizontal sum of the vector
    uint64_t partial_sum = vgetq_lane_u32(sum_vec, 0) +
                           vgetq_lane_u32(sum_vec, 1) +
                           vgetq_lane_u32(sum_vec, 2) +
                           vgetq_lane_u32(sum_vec, 3);

    *sum += partial_sum;

    // Process remaining elements
    end = buf + (size & 15);
    while (buf < end) {
        *sum += *buf;
        buf++;
    }
}