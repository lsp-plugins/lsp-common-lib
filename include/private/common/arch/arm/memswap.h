/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 14 июл. 2026 г.
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

#ifndef PRIVATE_COMMON_ARCH_ARM_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_ARM_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_ARM_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_ARM_IMPL */

namespace lsp
{
    namespace arm
    {
        void memswap(void *a, void *b, size_t count)
        {
            IF_ARCH_ARM(
                register void *reg_a        asm("r0") = a;
                register void *reg_b        asm("r1") = b;
                register size_t reg_count   asm("r2") = count;
            );

            ARCH_ARM_ASM
            (
                // Small block size checks
                __ASM_EMIT("subs        %[count], #0x08")
                __ASM_EMIT("blo         20f")

                // Store registers and test for alignment
                __ASM_EMIT("push        {r4-r11}")
                __ASM_EMIT("tst         %[a], #7")
                __ASM_EMIT("bne         10f")
                __ASM_EMIT("tst         %[b], #7")
                __ASM_EMIT("bne         10f")

                // ----------------------------------------
                // Aligned memory swap
                __ASM_EMIT("subs        %[count], #0x08")
                __ASM_EMIT("blo         2f")
                // 16-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("ldrd        r4, r5, [%[a], #0x00]")
                __ASM_EMIT("ldrd        r6, r7, [%[a], #0x08]")
                __ASM_EMIT("ldrd        r8, r9, [%[b], #0x00]")
                __ASM_EMIT("ldrd        r10, r11, [%[b], #0x08]")
                __ASM_EMIT("subs        %[count], #0x10")
                __ASM_EMIT("strd        r4, r5, [%[b]], #0x08")
                __ASM_EMIT("strd        r6, r7, [%[b]], #0x08")
                __ASM_EMIT("strd        r8, r9, [%[a]], #0x08")
                __ASM_EMIT("strd        r10, r11, [%[a]], #0x08")
                __ASM_EMIT("bhs         1b")
                // 8-byte block
                __ASM_EMIT("2:")
                __ASM_EMIT("adds        %[count], #0x08")
                __ASM_EMIT("blt         4f")
                __ASM_EMIT("ldrd        r4, r5, [%[a], #0x00]")
                __ASM_EMIT("ldrd        r8, r9, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], #0x08")
                __ASM_EMIT("strd        r4, r5, [%[b]], #0x08")
                __ASM_EMIT("strd        r8, r9, [%[a]], #0x08")
                // End
                __ASM_EMIT("4:")
                __ASM_EMIT("pop         {r4-r11}")
                __ASM_EMIT("b           20f")

                // ----------------------------------------
                // Unaligned memory swap
                __ASM_EMIT("10:")
                __ASM_EMIT("subs        %[count], #0x08")
                __ASM_EMIT("blo         12f")
                // 16-byte blocks
                __ASM_EMIT("11:")
                __ASM_EMIT("ldr         r4, [%[a], #0x00]")
                __ASM_EMIT("ldr         r5, [%[a], #0x04]")
                __ASM_EMIT("ldr         r6, [%[a], #0x08]")
                __ASM_EMIT("ldr         r7, [%[a], #0x0c]")
                __ASM_EMIT("ldr         r8, [%[b], #0x00]")
                __ASM_EMIT("ldr         r9, [%[b], #0x04]")
                __ASM_EMIT("ldr         r10, [%[b], #0x08]")
                __ASM_EMIT("ldr         r11, [%[b], #0x0c]")
                __ASM_EMIT("subs        %[count], #0x10")
                __ASM_EMIT("str         r4, [%[b]], #0x04")
                __ASM_EMIT("str         r5, [%[b]], #0x04")
                __ASM_EMIT("str         r6, [%[b]], #0x04")
                __ASM_EMIT("str         r7, [%[b]], #0x04")
                __ASM_EMIT("str         r8, [%[a]], #0x04")
                __ASM_EMIT("str         r9, [%[a]], #0x04")
                __ASM_EMIT("str         r10, [%[a]], #0x04")
                __ASM_EMIT("str         r11, [%[a]], #0x04")
                __ASM_EMIT("bhs         11b")
                // 8-byte block
                __ASM_EMIT("12:")
                __ASM_EMIT("adds        %[count], #0x08")
                __ASM_EMIT("blt         14f")
                __ASM_EMIT("ldr         r4, [%[a], #0x00]")
                __ASM_EMIT("ldr         r5, [%[a], #0x04]")
                __ASM_EMIT("ldr         r8, [%[b], #0x00]")
                __ASM_EMIT("ldr         r9, [%[b], #0x04]")
                __ASM_EMIT("subs        %[count], #0x08")
                __ASM_EMIT("str         r4, [%[b]], #0x04")
                __ASM_EMIT("str         r5, [%[b]], #0x04")
                __ASM_EMIT("str         r8, [%[a]], #0x04")
                __ASM_EMIT("str         r9, [%[a]], #0x04")
                // End
                __ASM_EMIT("14:")
                __ASM_EMIT("pop         {r4-r11}")

                // ----------------------------------------
                // Tail
                // 4-byte block
                __ASM_EMIT("20:")
                __ASM_EMIT("adds        %[count], #0x04")
                __ASM_EMIT("blt         22f")
                __ASM_EMIT("ldr         r3, [%[a], #0x00]")
                __ASM_EMIT("ldr         r12, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], #0x04")
                __ASM_EMIT("str         r3, [%[b]], #0x04")
                __ASM_EMIT("str         r12, [%[a]], #0x04")
                // 1-byte blocks
                __ASM_EMIT("22:")
                __ASM_EMIT("adds        %[count], #0x03")
                __ASM_EMIT("blt         24f")
                __ASM_EMIT("23:")
                __ASM_EMIT("ldrb        r3, [%[a], #0x00]")
                __ASM_EMIT("ldrb        r12, [%[b], #0x00]")
                __ASM_EMIT("subs        %[count], #0x01")
                __ASM_EMIT("strb        r3, [%[b]], #0x01")
                __ASM_EMIT("strb        r12, [%[a]], #0x01")
                __ASM_EMIT("bge         23b")
                // End
                __ASM_EMIT("24:")

                : [count] "+r" (reg_count),
                  [a] "+r" (reg_a), [b] "+r" (reg_b)
                :
                : "cc", "memory",
                  "r3", "r12"
            );
        }

    } /* namespace arm */
} /* namespace lsp */


#endif /* PRIVATE_COMMON_ARCH_ARM_MEMSWAP_H_ */
