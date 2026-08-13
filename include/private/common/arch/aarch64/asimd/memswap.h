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

#ifndef INCLUDE_PRIVATE_COMMON_ARCH_AARCH64_ASIMD_MEMSWAP_H_
#define INCLUDE_PRIVATE_COMMON_ARCH_AARCH64_ASIMD_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_AARCH64_ASIMD_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_AARCH64_ASIMD_IMPL */

namespace lsp
{
    namespace asimd
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
                __ASM_EMIT("subs        %[count], %[count], #0x70")
                __ASM_EMIT("b.lo        2f")
                // 128-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("ldp         q0, q1, [%[a], #0x00]")
                __ASM_EMIT("ldp         q2, q3, [%[a], #0x20]")
                __ASM_EMIT("ldp         q4, q5, [%[a], #0x40]")
                __ASM_EMIT("ldp         q6, q7, [%[a], #0x60]")
                __ASM_EMIT("ldp         q16, q17, [%[b], #0x00]")
                __ASM_EMIT("ldp         q18, q19, [%[b], #0x20]")
                __ASM_EMIT("ldp         q20, q21, [%[b], #0x40]")
                __ASM_EMIT("ldp         q22, q23, [%[b], #0x60]")
                __ASM_EMIT("subs        %[count], %[count], #0x80")
                __ASM_EMIT("stp         q0, q1, [%[b]], #0x80")
                __ASM_EMIT("stp         q2, q3, [%[b], #-0x60]")
                __ASM_EMIT("stp         q4, q5, [%[b], #-0x40]")
                __ASM_EMIT("stp         q6, q7, [%[b], #-0x20]")
                __ASM_EMIT("stp         q16, q17, [%[a]], #0x80")
                __ASM_EMIT("stp         q18, q19, [%[a], #-0x60]")
                __ASM_EMIT("stp         q20, q21, [%[a], #-0x40]")
                __ASM_EMIT("stp         q22, q23, [%[a], #-0x20]")
                __ASM_EMIT("b.hs        1b")
                // 64-byte block
                __ASM_EMIT("2:")
                __ASM_EMIT("adds        %[count], %[count], #0x40")
                __ASM_EMIT("b.lt        4f")
                __ASM_EMIT("ldp         q0, q1, [%[a], #0x00]")
                __ASM_EMIT("ldp         q2, q3, [%[a], #0x20]")
                __ASM_EMIT("ldp         q4, q5, [%[b], #0x00]")
                __ASM_EMIT("ldp         q6, q7, [%[b], #0x20]")
                __ASM_EMIT("sub         %[count], %[count], #0x40")
                __ASM_EMIT("stp         q0, q1, [%[b]], #0x40")
                __ASM_EMIT("stp         q2, q3, [%[b], #-0x20]")
                __ASM_EMIT("stp         q4, q5, [%[a]], #0x40")
                __ASM_EMIT("stp         q6, q7, [%[a], #-0x20]")
                // 32-byte blocks
                __ASM_EMIT("4:")
                __ASM_EMIT("adds        %[count], %[count], #0x20")
                __ASM_EMIT("b.lt        6f")
                __ASM_EMIT("ldp         q0, q1, [%[a], #0x00]")
                __ASM_EMIT("ldp         q4, q5, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], %[count], #0x20")
                __ASM_EMIT("stp         q0, q1, [%[b]], #0x20")
                __ASM_EMIT("stp         q4, q5, [%[a]], #0x20")
                // 16-byte block
                __ASM_EMIT("6:")
                __ASM_EMIT("adds        %[count], %[count], #0x10")
                __ASM_EMIT("b.lt        8f")
                __ASM_EMIT("ldr         q0, [%[a], #0x00]")
                __ASM_EMIT("ldr         q4, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], %[count], #0x10")
                __ASM_EMIT("str         q0, [%[b]], #0x10")
                __ASM_EMIT("str         q4, [%[a]], #0x10")
                // End
                __ASM_EMIT("8:")

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
                  "x3", "x12",
                  "v0", "v1", "v2", "v3",
                  "v4", "v5", "v6", "v7",
                  "v16", "v17", "v18", "v19",
                  "v20", "v21", "v22", "v23"
            );
        }

    } /* namespace asimd */
} /* namespace lsp */



#endif /* PRIVATE_COMMON_ARCH_AARCH64_ASIMD_MEMSWAP_H_ */
