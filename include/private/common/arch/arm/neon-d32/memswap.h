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

#ifndef PRIVATE_COMMON_ARCH_ARM_NEON_D32_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_ARM_NEON_D32_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_ARM_NEON_D32_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_ARM_NEON_D32_IMPL */

namespace lsp
{
    namespace neon_d32
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
                __ASM_EMIT("subs        %[count], #0x10")
                __ASM_EMIT("blo         24f")
                __ASM_EMIT("subs        %[count], #0x30")
                __ASM_EMIT("blo         20f")

                // Store registers and test for alignment
                __ASM_EMIT("tst         %[a], #0x0f")
                __ASM_EMIT("bne         10f")
                __ASM_EMIT("tst         %[b], #0x0f")
                __ASM_EMIT("bne         10f")

                // ----------------------------------------
                // Aligned memory swap
                // 64-byte blocks
                __ASM_EMIT("1:")
                __ASM_EMIT("vldm        %[a], {q0-q1}")
                __ASM_EMIT("vldm        %[b], {q2-q3}")
                __ASM_EMIT("vstm        %[b]!, {q0-q1}")
                __ASM_EMIT("vstm        %[a]!, {q2-q3}")
                __ASM_EMIT("subs        %[count], #0x40")
                __ASM_EMIT("vldm        %[a], {q0-q1}")
                __ASM_EMIT("vldm        %[b], {q2-q3}")
                __ASM_EMIT("vstm        %[b]!, {q0-q1}")
                __ASM_EMIT("vstm        %[a]!, {q2-q3}")
                __ASM_EMIT("bhs         1b")
                // End
                __ASM_EMIT("b           20f")

                // ----------------------------------------
                // Unaligned memory swap
                __ASM_EMIT("10:")
                // 64-byte blocks
                __ASM_EMIT("11:")
                __ASM_EMIT("vld1.8      {d0-d3}, [%[a]]")
                __ASM_EMIT("vld1.8      {d4-d7}, [%[b]]")
                __ASM_EMIT("vst1.8      {d0-d3}, [%[b]]!")
                __ASM_EMIT("vst1.8      {d4-d7}, [%[a]]!")
                __ASM_EMIT("subs        %[count], #0x40")
                __ASM_EMIT("vld1.8      {d0-d3}, [%[a]]")
                __ASM_EMIT("vld1.8      {d4-d7}, [%[b]]")
                __ASM_EMIT("vst1.8      {d0-d3}, [%[b]]!")
                __ASM_EMIT("vst1.8      {d4-d7}, [%[a]]!")
                __ASM_EMIT("bhs         11b")
                // End

                // ----------------------------------------
                // Tail
                // 32-byte block
                __ASM_EMIT("20:")
                __ASM_EMIT("adds        %[count], #0x20")
                __ASM_EMIT("blt         22f")
                __ASM_EMIT("vld1.8      {d0-d3}, [%[a]]")
                __ASM_EMIT("vld1.8      {d4-d7}, [%[b]]")
                __ASM_EMIT("sub         %[count], #0x20")
                __ASM_EMIT("vst1.8      {d0-d3}, [%[b]]!")
                __ASM_EMIT("vst1.8      {d4-d7}, [%[a]]!")
                // 16-byte block
                __ASM_EMIT("22:")
                __ASM_EMIT("adds        %[count], #0x10")
                __ASM_EMIT("blt         24f")
                __ASM_EMIT("vld1.8      {d0, d1}, [%[a]]")
                __ASM_EMIT("vld1.8      {d2, d3}, [%[b]]")
                __ASM_EMIT("sub         %[count], #0x10")
                __ASM_EMIT("vst1.8      {d0, d1}, [%[b]]!")
                __ASM_EMIT("vst1.8      {d2, d3}, [%[a]]!")
                // 8-byte block
                __ASM_EMIT("24:")
                __ASM_EMIT("adds        %[count], #0x08")
                __ASM_EMIT("blt         26f")
                __ASM_EMIT("vld1.8      {d0}, [%[a]]")
                __ASM_EMIT("vld1.8      {d1}, [%[b]]")
                __ASM_EMIT("sub         %[count], #0x08")
                __ASM_EMIT("vst1.8      {d0}, [%[b]]!")
                __ASM_EMIT("vst1.8      {d1}, [%[a]]!")
                // 4-byte block
                __ASM_EMIT("26:")
                __ASM_EMIT("adds        %[count], #0x04")
                __ASM_EMIT("blt         28f")
                __ASM_EMIT("ldr         r3, [%[a], #0x00]")
                __ASM_EMIT("ldr         r12, [%[b], #0x00]")
                __ASM_EMIT("sub         %[count], #0x04")
                __ASM_EMIT("str         r3, [%[b]], #0x04")
                __ASM_EMIT("str         r12, [%[a]], #0x04")
                // 1-byte blocks
                __ASM_EMIT("28:")
                __ASM_EMIT("adds        %[count], #0x03")
                __ASM_EMIT("blt         30f")
                __ASM_EMIT("29:")
                __ASM_EMIT("ldrb        r3, [%[a], #0x00]")
                __ASM_EMIT("ldrb        r12, [%[b], #0x00]")
                __ASM_EMIT("subs        %[count], #0x01")
                __ASM_EMIT("strb        r3, [%[b]], #0x01")
                __ASM_EMIT("strb        r12, [%[a]], #0x01")
                __ASM_EMIT("bge         29b")
                // End
                __ASM_EMIT("30:")

                : [count] "+r" (reg_count),
                  [a] "+r" (reg_a), [b] "+r" (reg_b)
                :
                : "cc", "memory",
                  "r3", "r12",
                  "q0", "q1", "q2", "q3"
            );
        }

    } /* namespace neon_d32 */
} /* namespace lsp */

#endif /* PRIVATE_COMMON_ARCH_ARM_NEON_D32_MEMSWAP_H_ */
