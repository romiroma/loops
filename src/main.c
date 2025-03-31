#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tests.h"

const uint16_t BUFFER_SIZE = 63999;

int main() {
    clock_t start, end;
    double cpu_time_used;
    // start = clock();
    // printf("hello, world!\n");
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    uint16_t i;
    uint16_t *buf = malloc(BUFFER_SIZE * sizeof(uint16_t));
    uint16_t *buf1 = malloc(BUFFER_SIZE * sizeof(uint16_t));
    uint16_t *buf2 = malloc(BUFFER_SIZE * sizeof(uint16_t));
    uint16_t *buf3 = malloc(BUFFER_SIZE * sizeof(uint16_t));
    uint16_t *buf4 = malloc(BUFFER_SIZE * sizeof(uint16_t));
    uint64_t sum = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

    for (i = 0; i < BUFFER_SIZE; i++) {
        buf[i] = i;
        buf1[i] = i;
        buf2[i] = i;
        buf3[i] = i;
        buf4[i] = i;
    }
        
    printf("BUFFER SIZE: %u\n", BUFFER_SIZE);

    start = clock();
    test_c_for_i(buf, BUFFER_SIZE, &sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("test_c_for_i: %f seconds, SUM: %lu\n", cpu_time_used, sum);

    start = clock();
    test_c_for_each(buf1, BUFFER_SIZE, &sum1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("test_c_for_each: %f seconds, SUM: %lu\n", cpu_time_used, sum1);

    start = clock();  
    test_c_while(buf2, BUFFER_SIZE, &sum2);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("test_c_while: %f seconds, SUM: %lu\n", cpu_time_used, sum2);

    start = clock();  
    test_c_simd(buf3, BUFFER_SIZE, &sum3);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("test_c_simd: %f seconds, SUM: %lu\n", cpu_time_used, sum3);

    start = clock();
    test_asm_simd(buf4, BUFFER_SIZE, &sum4);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("test_asm_simd: %f seconds, SUM: %lu\n", cpu_time_used, sum4);

    free(buf);
    free(buf1);
    free(buf2);
    free(buf3);
    free(buf4);

    if (sum != sum1 || sum != sum2 || sum != sum3 || sum != sum4) {
        return -1;
    } else {
        return 0;    
    }
}
