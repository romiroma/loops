#### Creates buffers with populating it with 0...BUFFER_SIZE (const uint16_t BUFFER_SIZE in main.c). Calculates sum of all elements 
#### x86_64/arm64/aarch64


##### Example
```
$ ./run_tests.sh -O3
Starting the build process...
BUFFER SIZE: 63999
test_c_for_i: 0.000047 seconds, SUM: 2047904001
test_c_for_each: 0.000046 seconds, SUM: 2047904001
test_c_while: 0.000046 seconds, SUM: 2047904001
test_c_simd: 0.000043 seconds, SUM: 2047904001
test_asm_simd: 0.000036 seconds, SUM: 2047904001
All tests passed.
All files cleaned up.
```

```
$ ./run_tests.sh -O0
Starting the build process...
BUFFER SIZE: 63999
test_c_for_i: 0.000583 seconds, SUM: 2047904001
test_c_for_each: 0.000490 seconds, SUM: 2047904001
test_c_while: 0.000491 seconds, SUM: 2047904001
test_c_simd: 0.000298 seconds, SUM: 2047904001
test_asm_simd: 0.000059 seconds, SUM: 2047904001
All tests passed.
All files cleaned up.
```
