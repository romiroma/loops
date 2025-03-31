#include <stdint.h>
#include <stdlib.h>

#include "tests.h"

void test_c_for_i(uint16_t *buf, const uint16_t size, uint64_t *sum) {
    for (uint16_t i = 0; i < size; i++)
        *sum += buf[i];
}

void test_c_for_each(uint16_t *buf, const uint16_t size, uint64_t *sum) {
    uint16_t *end;
    for (end = buf + size; buf - end;)
        *sum += *buf++;
}

void test_c_while(uint16_t *buf, const uint16_t size, uint64_t *sum) {
    const uint16_t *end = buf + size;

    while (buf - end)
        *sum += *buf++;
}
