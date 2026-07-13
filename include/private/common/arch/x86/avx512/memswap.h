/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 13 июл. 2026 г.
 *
 * lsp-common-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-common-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-common-lib. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PRIVATE_COMMON_ARCH_X86_AVX512_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_X86_AVX512_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_X86_AVX512_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_X86_AVX512_IMPL */

namespace lsp
{
    namespace avx512
    {
        void memswap(void *a, void *b, size_t count)
        {
            IF_ARCH_X86(size_t ta, tb);
            ARCH_X86_ASM
            (
                // Small block size checks
                __ASM_EMIT("sub         $0x10, %[count]")
                __ASM_EMIT("jb          10f")
                // 256-byte blocks
                __ASM_EMIT("sub         $0xf0, %[count]")
                __ASM_EMIT("jb          2f")
                __ASM_EMIT(".p2align    4")
                __ASM_EMIT("1:")
                __ASM_EMIT("vmovups     0x00(%[a]), %%zmm0")
                __ASM_EMIT("vmovups     0x40(%[a]), %%zmm1")
                __ASM_EMIT("vmovups     0x80(%[a]), %%zmm2")
                __ASM_EMIT("vmovups     0xc0(%[a]), %%zmm3")
                __ASM_EMIT("vmovups     0x00(%[b]), %%zmm4")
                __ASM_EMIT("vmovups     0x40(%[b]), %%zmm5")
                __ASM_EMIT("vmovups     0x80(%[b]), %%zmm6")
                __ASM_EMIT("vmovups     0xc0(%[b]), %%zmm7")
                __ASM_EMIT("vmovups     %%zmm4, 0x00(%[a])")
                __ASM_EMIT("vmovups     %%zmm5, 0x40(%[a])")
                __ASM_EMIT("vmovups     %%zmm6, 0x80(%[a])")
                __ASM_EMIT("vmovups     %%zmm7, 0xc0(%[a])")
                __ASM_EMIT("vmovups     %%zmm0, 0x00(%[b])")
                __ASM_EMIT("vmovups     %%zmm1, 0x40(%[b])")
                __ASM_EMIT("vmovups     %%zmm2, 0x80(%[b])")
                __ASM_EMIT("vmovups     %%zmm3, 0xc0(%[b])")
                __ASM_EMIT("add         $0x100, %[a]")
                __ASM_EMIT("add         $0x100, %[b]")
                __ASM_EMIT("sub         $0x100, %[count]")
                __ASM_EMIT("jae         1b")
                // 128-byte block
                __ASM_EMIT("2:")
                __ASM_EMIT("add         $0x80, %[count]")
                __ASM_EMIT("jl          4f")
                __ASM_EMIT("vmovups     0x00(%[a]), %%zmm0")
                __ASM_EMIT("vmovups     0x40(%[a]), %%zmm1")
                __ASM_EMIT("vmovups     0x00(%[b]), %%zmm4")
                __ASM_EMIT("vmovups     0x40(%[b]), %%zmm5")
                __ASM_EMIT("vmovups     %%zmm4, 0x00(%[a])")
                __ASM_EMIT("vmovups     %%zmm5, 0x40(%[a])")
                __ASM_EMIT("vmovups     %%zmm0, 0x00(%[b])")
                __ASM_EMIT("vmovups     %%zmm1, 0x40(%[b])")
                __ASM_EMIT("sub         $0x80, %[count]")
                __ASM_EMIT("add         $0x80, %[a]")
                __ASM_EMIT("add         $0x80, %[b]")
                // 64-byte blocks
                __ASM_EMIT("4:")
                __ASM_EMIT("add         $0x40, %[count]")
                __ASM_EMIT("jl          6f")
                __ASM_EMIT("vmovups     0x00(%[a]), %%zmm0")
                __ASM_EMIT("vmovups     0x00(%[b]), %%zmm4")
                __ASM_EMIT("vmovups     %%zmm4, 0x00(%[a])")
                __ASM_EMIT("vmovups     %%zmm0, 0x00(%[b])")
                __ASM_EMIT("sub         $0x40, %[count]")
                __ASM_EMIT("add         $0x40, %[a]")
                __ASM_EMIT("add         $0x40, %[b]")
                // 32-byte block
                __ASM_EMIT("6:")
                __ASM_EMIT("add         $0x20, %[count]")
                __ASM_EMIT("jl          8f")
                __ASM_EMIT("vmovups     0x00(%[a]), %%ymm0")
                __ASM_EMIT("vmovups     0x00(%[b]), %%ymm4")
                __ASM_EMIT("vmovups     %%ymm4, 0x00(%[a])")
                __ASM_EMIT("vmovups     %%ymm0, 0x00(%[b])")
                __ASM_EMIT("sub         $0x20, %[count]")
                __ASM_EMIT("add         $0x20, %[a]")
                __ASM_EMIT("add         $0x20, %[b]")
                // 16-byte block
                __ASM_EMIT("8:")
                __ASM_EMIT("add         $0x10, %[count]")
                __ASM_EMIT("jl          10f")
                __ASM_EMIT("vmovups     0x00(%[a]), %%xmm0")
                __ASM_EMIT("vmovups     0x00(%[b]), %%xmm4")
                __ASM_EMIT("vmovups     %%xmm4, 0x00(%[a])")
                __ASM_EMIT("vmovups     %%xmm0, 0x00(%[b])")
                __ASM_EMIT("sub         $0x10, %[count]")
                __ASM_EMIT("add         $0x10, %[a]")
                __ASM_EMIT("add         $0x10, %[b]")
                // 8-byte block
                __ASM_EMIT("10:")
                __ASM_EMIT("add         $0x08, %[count]")
                __ASM_EMIT("jl          12f")
                __ASM_EMIT("vmovlps     0x00(%[a]), %%xmm0, %%xmm0")
                __ASM_EMIT("vmovlps     0x00(%[b]), %%xmm4, %%xmm4")
                __ASM_EMIT("vmovlps     %%xmm4, 0x00(%[a])")
                __ASM_EMIT("vmovlps     %%xmm0, 0x00(%[b])")
                __ASM_EMIT("sub         $0x08, %[count]")
                __ASM_EMIT("add         $0x08, %[a]")
                __ASM_EMIT("add         $0x08, %[b]")
                // 4-byte block
                __ASM_EMIT("12:")
                __ASM_EMIT("add         $0x04, %[count]")
                __ASM_EMIT("jl          14f")
                __ASM_EMIT("vmovss      0x00(%[a]), %%xmm0")
                __ASM_EMIT("vmovss      0x00(%[b]), %%xmm4")
                __ASM_EMIT("vmovss      %%xmm4, 0x00(%[a])")
                __ASM_EMIT("vmovss      %%xmm0, 0x00(%[b])")
                __ASM_EMIT("sub         $0x04, %[count]")
                __ASM_EMIT("add         $0x04, %[a]")
                __ASM_EMIT("add         $0x04, %[b]")
                // 1-byte blocks
                __ASM_EMIT("14:")
                __ASM_EMIT("add         $3, %[count]")
                __ASM_EMIT("jl          16f")
                __ASM_EMIT("15:")
                __ASM_EMIT("mov         0x00(%[a]), %b[ta]")
                __ASM_EMIT("mov         0x00(%[b]), %b[tb]")
                __ASM_EMIT("mov         %b[tb], 0x00(%[a])")
                __ASM_EMIT("mov         %b[ta], 0x00(%[b])")
                __ASM_EMIT("add         $0x01, %[a]")
                __ASM_EMIT("add         $0x01, %[b]")
                __ASM_EMIT("dec         %[count]")
                __ASM_EMIT("jge         15b")
                // End
                __ASM_EMIT("16:")
                : [a] "+r" (a), [b] "+r" (b),
                  [ta] "=&R" (ta), [tb] "=&R" (tb),
                  [count] "+r" (count)
                :
                : "cc", "memory",
                  "%xmm0", "%xmm1", "%xmm2", "%xmm3",
                  "%xmm4", "%xmm5", "%xmm6", "%xmm7"
            );
        }

    } /* namespace avx512 */
} /* namespace lsp */



#endif /* PRIVATE_COMMON_ARCH_X86_AVX512_MEMSWAP_H_ */
