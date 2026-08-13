/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 16 июл. 2026 г.
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

#ifndef PRIVATE_COMMON_ARCH_AARCH64_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_AARCH64_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_AARCH64_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_AARCH64_IMPL */

namespace lsp
{
    namespace aarch64
    {
        void memswap(void *a, void *b, size_t count)
        {
            IF_ARCH_AARCH64(
                register void *reg_a        asm("x0") = a;
                register void *reg_b        asm("x1") = b;
                register size_t reg_count   asm("x2") = count;
            );

            ARCH_AARCH64_ASM
            (
                // Small block size checks
                __ASM_EMIT("subs        %[count], %[count], #0x10")
                __ASM_EMIT("b.lo        10f")

                // Store registers and perform memory swap
                __ASM_EMIT("subs        %[count], %[count], #0x10")
                __ASM_EMIT("b.lo        2f")
                // 32-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("ldp         x4, x5, [%[a], #0x00]")
                __ASM_EMIT("ldp         x6, x7, [%[a], #0x10]")
                __ASM_EMIT("ldp         x8, x9, [%[b], #0x00]")
                __ASM_EMIT("ldp         x10, x11, [%[b], #0x10]")
                __ASM_EMIT("subs        %[count], %[count], #0x20")
                __ASM_EMIT("stp         x4, x5, [%[b]], #0x20")
                __ASM_EMIT("stp         x6, x7, [%[b], #-0x10]")
                __ASM_EMIT("stp         x8, x9, [%[a]], #0x20")
                __ASM_EMIT("stp         x10, x11, [%[a], #-0x10]")
                __ASM_EMIT("b.hs        1b")
                // 16-byte block
                __ASM_EMIT("2:")
                __ASM_EMIT("adds        %[count], %[count], #0x10")
                __ASM_EMIT("b.lt        4f")
                __ASM_EMIT("ldp         x4, x5, [%[a], #0x00]")
                __ASM_EMIT("ldp         x6, x7, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], %[count], #0x10")
                __ASM_EMIT("stp         x4, x5, [%[b]], #0x10")
                __ASM_EMIT("stp         x6, x7, [%[a]], #0x10")
                // End
                __ASM_EMIT("4:")

                // ----------------------------------------
                // Tail
                // 8-byte block
                __ASM_EMIT("10:")
                __ASM_EMIT("adds        %[count], %[count], #0x08")
                __ASM_EMIT("b.lt        12f")
                __ASM_EMIT("ldr         x3, [%[a], #0x00]")
                __ASM_EMIT("ldr         x12, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], %[count], #0x08")
                __ASM_EMIT("str         x3, [%[b]], #0x08")
                __ASM_EMIT("str         x12, [%[a]], #0x08")
                // 4-byte block
                __ASM_EMIT("12:")
                __ASM_EMIT("adds        %[count], %[count], #0x04")
                __ASM_EMIT("b.lt        14f")
                __ASM_EMIT("ldr         w3, [%[a], #0x00]")
                __ASM_EMIT("ldr         w12, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], %[count], #0x04")
                __ASM_EMIT("str         w3, [%[b]], #0x04")
                __ASM_EMIT("str         w12, [%[a]], #0x04")
                // 1-byte blocks
                __ASM_EMIT("14:")
                __ASM_EMIT("adds        %[count], %[count], #0x03")
                __ASM_EMIT("b.lt        16f")
                __ASM_EMIT("15:")
                __ASM_EMIT("ldrb        w3, [%[a], #0x00]")
                __ASM_EMIT("ldrb        w12, [%[b], #0x00]")
                __ASM_EMIT("subs        %[count], %[count], #0x01")
                __ASM_EMIT("strb        w3, [%[b]], #0x01")
                __ASM_EMIT("strb        w12, [%[a]], #0x01")
                __ASM_EMIT("b.ge        15b")
                // End
                __ASM_EMIT("16:")

                : [count] "+r" (reg_count),
                  [a] "+r" (reg_a), [b] "+r" (reg_b)
                :
                : "cc", "memory",
                  "x3",
                  "x4", "x5", "x6", "x7",
                  "x8", "x9", "x10", "x11",
                  "x12"
            );
        }

    } /* namespace aarch64 */
} /* namespace lsp */



#endif /* PRIVATE_COMMON_ARCH_AARCH64_MEMSWAP_H_ */
