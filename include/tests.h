#ifndef TESTS_H
#define TESTS_H

void test_c_for_i(uint16_t *buf, const uint16_t size, uint64_t *sum);
void test_c_for_each(uint16_t *buf, const uint16_t size, uint64_t *sum);
void test_c_while(uint16_t *buf, const uint16_t size, uint64_t *sum);
void test_c_simd(uint16_t *buf, const uint16_t size, uint64_t *sum);
void test_asm_simd(uint16_t* buf, uint16_t size, uint64_t* sum);

#endif // TESTS_H