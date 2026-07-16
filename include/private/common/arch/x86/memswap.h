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

#ifndef PRIVATE_COMMON_ARCH_X86_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_X86_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_X86_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_X86_IMPL */

namespace lsp
{
    namespace x86
    {
#ifdef ARCH_64BIT
        void memswap(void *a, void *b, size_t count)
        {
            IF_ARCH_X86(
                size_t off;
                size_t ta0, tb0;
                size_t ta1, tb1;
            );
            ARCH_X86_ASM
            (
                // Small block size checks
                __ASM_EMIT("xor         %[off], %[off]")
                __ASM_EMIT("sub         $0x10, %[count]")
                __ASM_EMIT("jb          2f")
                // 16-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("mov         0x00(%[a], %[off]), %[ta0]")
                __ASM_EMIT("mov         0x08(%[a], %[off]), %[ta1]")
                __ASM_EMIT("mov         0x00(%[b], %[off]), %[tb0]")
                __ASM_EMIT("mov         0x08(%[b], %[off]), %[tb1]")
                __ASM_EMIT("mov         %[tb0], 0x00(%[a], %[off])")
                __ASM_EMIT("mov         %[tb1], 0x08(%[a], %[off])")
                __ASM_EMIT("mov         %[ta0], 0x00(%[b], %[off])")
                __ASM_EMIT("mov         %[ta1], 0x08(%[b], %[off])")
                __ASM_EMIT("add         $0x10, %[off]")
                __ASM_EMIT("sub         $0x10, %[count]")
                __ASM_EMIT("jae         1b")
                // 8-byte block
                __ASM_EMIT("2:")
                __ASM_EMIT("add         $0x08, %[count]")
                __ASM_EMIT("jl          4f")
                __ASM_EMIT("mov         0x00(%[a], %[off]), %[ta0]")
                __ASM_EMIT("mov         0x00(%[b], %[off]), %[tb0]")
                __ASM_EMIT("mov         %[tb0], 0x00(%[a], %[off])")
                __ASM_EMIT("mov         %[ta0], 0x00(%[b], %[off])")
                __ASM_EMIT("sub         $0x08, %[count]")
                __ASM_EMIT("add         $0x08, %[off]")
                // 4-byte block
                __ASM_EMIT("4:")
                __ASM_EMIT("add         $0x04, %[count]")
                __ASM_EMIT("jl          6f")
                __ASM_EMIT("mov         0x00(%[a], %[off]), %k[ta0]")
                __ASM_EMIT("mov         0x00(%[b], %[off]), %k[tb0]")
                __ASM_EMIT("mov         %k[tb0], 0x00(%[a], %[off])")
                __ASM_EMIT("mov         %k[ta0], 0x00(%[b], %[off])")
                __ASM_EMIT("sub         $0x04, %[count]")
                __ASM_EMIT("add         $0x04, %[off]")
                // 1-byte blocks
                __ASM_EMIT("6:")
                __ASM_EMIT("add         $3, %[count]")
                __ASM_EMIT("jl          8f")
                __ASM_EMIT("11:")
                __ASM_EMIT("mov         0x00(%[a], %[off]), %b[ta0]")
                __ASM_EMIT("mov         0x00(%[b], %[off]), %b[tb0]")
                __ASM_EMIT("mov         %b[tb0], 0x00(%[a], %[off])")
                __ASM_EMIT("mov         %b[ta0], 0x00(%[b], %[off])")
                __ASM_EMIT("add         $0x01, %[off]")
                __ASM_EMIT("dec         %[count]")
                __ASM_EMIT("jge         11b")
                // End
                __ASM_EMIT("8:")
                : [count] "+r" (count),
                  [off] "=&r" (off),
                  [ta0] "=&r" (ta0), [tb0] "=&r" (tb0),
                  [ta1] "=&r" (ta1), [tb1] "=&r" (tb1)
                : [a] "r" (a), [b] "r" (b)
                : "cc", "memory"
            );
        }
#endif /* ARCH_64BIT */

#ifdef ARCH_32BIT
        void memswap(void *a, void *b, size_t count)
        {
            IF_ARCH_X86(
                size_t ta, tb;
            );
            ARCH_X86_ASM
            (
                // Small block size checks
                __ASM_EMIT("xor         %[off]")
                __ASM_EMIT("sub         $0x04, %[count]")
                __ASM_EMIT("jb          2f")
                // 4-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("mov         0x00(%[a]), %k[ta]")
                __ASM_EMIT("mov         0x00(%[b]), %k[tb]")
                __ASM_EMIT("mov         %k[tb], 0x00(%[a])")
                __ASM_EMIT("mov         %k[ta], 0x00(%[b])")
                __ASM_EMIT("add         $0x04, %[a]")
                __ASM_EMIT("add         $0x04, %[b]")
                __ASM_EMIT("sub         $0x04, %[count]")
                __ASM_EMIT("jae         1b")
                // 1-byte blocks
                __ASM_EMIT("2:")
                __ASM_EMIT("add         $3, %[count]")
                __ASM_EMIT("jl          4f")
                __ASM_EMIT("11:")
                __ASM_EMIT("mov         0x00(%[a]), %b[ta]")
                __ASM_EMIT("mov         0x00(%[b]), %b[tb]")
                __ASM_EMIT("mov         %b[tb], 0x00(%[a])")
                __ASM_EMIT("mov         %b[ta], 0x00(%[b])")
                __ASM_EMIT("add         $0x01, %[a]")
                __ASM_EMIT("add         $0x01, %[b]")
                __ASM_EMIT("dec         %[count]")
                __ASM_EMIT("jge         11b")
                // End
                __ASM_EMIT("4:")
                : [a] "+r" (a), [b] "+r" (b),
                  [count] "+r" (count),
                  [ta] "=&r" (ta), [tb] "=&r" (tb)
                :
                : "cc", "memory"
            );
        }

#endif /* ARCH_32BIT */

    } /* namespace x86 */
} /* namespace lsp */



#endif /* PRIVATE_COMMON_ARCH_X86_MEMSWAP_H_ */
