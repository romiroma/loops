section .text
global test_asm_simd

test_asm_simd:
    ; Arguments:
    ; rdi = buf (uint16_t*)
    ; rsi = size (const uint16_t)
    ; rdx = sum (uint64_t*)
    pxor xmm0, xmm0        ; Clear xmm0 (initialize SIMD sum to 0)
    pxor xmm1, xmm1        ; Clear xmm0 (initialize SIMD sum to 0)
    pxor xmm2, xmm2        ; Clear xmm0 (initialize SIMD sum to 0)

    ; Calculate end = buf + size
    movzx rcx, si          ; Zero-extend size (uint16_t) to rcx
    shl rcx, 1             ; Multiply size by 2 (size of uint16_t)
    add rcx, rdi           ; rcx = buf + size (end)

.simd_loop:
    cmp rdi, rcx           ; Compare buf with end
    jae .scalar_tail       ; If buf >= end, process remaining elements in scalar

    movdqu xmm1, [rdi]     ; Load 8 bytes (4 uint16_t) from buf into xmm1
    ; Convert 16-bit integers to 32-bit integers
    pmovzxwd xmm2, xmm1    ; Zero-extend words to doublewords
    paddd xmm0, xmm2       ; Add packed uint32_t values in xmm2 to xmm0
    add rdi, 8             ; Increment buf by 4 elements (8 bytes)
    jmp .simd_loop         ; Repeat SIMD loop

.scalar_tail:
    ; Horizontal sum of 4 uint64_t values in xmm0
    movhlps xmm1, xmm0       ; Move high 64 bits of xmm0 to low 64 bits of xmm1
    paddq xmm0, xmm1         ; Add packed uint64_t values in xmm0 and xmm1

    pshufd xmm1, xmm0, 0x1   ; Shuffle low 64 bits to high 64 bits in xmm1
    paddq xmm0, xmm1         ; Add packed uint64_t values in xmm0 and xmm1

    movd [rdx], xmm0         ; Store the final sum in the memory location pointed to by rdx


    ret