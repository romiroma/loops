.text
.globl test_asm_simd

test_asm_simd:
    // Arguments:
    // x0 = buf (uint16_t*)
    // x1 = size (const uint16_t)
    // x2 = sum (uint64_t*)
    movi v0.2d, #0          // Clear v0 (initialize SIMD sum to 0)

    and w3, w1, #0xFFFF     // Mask w1 to extract the lower 16 bits (uint16_t size)
    uxtw x3, w3             // Zero-extend w3 to x3

    // Calculate end = buf + size
    lsl x3, x3, #1          // Multiply size by 2 (size of uint16_t)
    add x3, x3, x0          // x3 = buf + size (end)

.simd_loop:
    cmp x0, x3              // Compare buf with end
    b.ge .scalar_tail       // If buf >= end, process remaining elements in scalar

    ld1 {v1.4h}, [x0], #8   // Load 4 uint16_t values from buf into v1 and increment buf
    ushll v2.4s, v1.4h, #0  // Zero-extend 16-bit integers to 32-bit integers
    add v0.4s, v0.4s, v2.4s // Add packed uint32_t values in v2 to v0
    b .simd_loop            // Repeat SIMD loop

.scalar_tail:
    // Horizontal sum of 4 uint32_t values in v0
    addv s0, v0.4s          // Reduce v0.4s horizontally into s0

    str s0, [x2]            // Store the final sum in the memory location pointed to by x2
    ret
    