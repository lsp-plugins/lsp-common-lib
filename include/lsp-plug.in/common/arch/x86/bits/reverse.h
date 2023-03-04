/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 1 апр. 2020 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_X86_BITS_REVERSE_H_
#define LSP_PLUG_IN_COMMON_ARCH_X86_BITS_REVERSE_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline uint8_t __lsp_forced_inline    reverse_bits(uint8_t v)
    {
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %[v], %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %[v]")
            : [v] "+q"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );

        return v;
    }

    inline int8_t __lsp_forced_inline    reverse_bits(int8_t v)
    {
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %[v], %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %[v]")
            : [v] "+q"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );

        return v;
    }

    inline uint8_t __lsp_forced_inline    reverse_bits(uint8_t v, size_t count)
    {
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %[v], %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %[v]")
            __ASM_EMIT("shr         %%cl, %[v]")
            : [v] "+q"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data), "c"(8-count)
            : "cc"
        );

        return v;
    }

    inline int8_t __lsp_forced_inline    reverse_bits(int8_t v, size_t count)
    {
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %[v], %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %[v]")
            __ASM_EMIT("shr         %%cl, %[v]")
            : [v] "+q"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data), "c"(8-count)
            : "cc"
        );

        return v;
    }

    inline uint16_t __lsp_forced_inline   reverse_bits(uint16_t v)
    {
    #ifdef ARCH_X86_64
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("ror         $8, %%ax")
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")

            : [v] "+a"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );
    #else
        size_t tmp1, tmp2;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp1]")
            __ASM_EMIT("movzx       %%ah, %[tmp2]")
            __ASM_EMIT("mov         (%[rb], %[tmp1]), %%ah")
            __ASM_EMIT("mov         (%[rb], %[tmp2]), %%al")
            : [v] "+a"(v), [tmp1] "=&r"(tmp1), [tmp2] "=&r"(tmp2)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );
    #endif /* ARCH_X86_64 */

        return v;
    }

    inline int16_t __lsp_forced_inline   reverse_bits(int16_t v)
    {
    #ifdef ARCH_X86_64
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("ror         $8, %%ax")
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")

            : [v] "+a"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );
    #else
        size_t tmp1, tmp2;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp1]")
            __ASM_EMIT("movzx       %%ah, %[tmp2]")
            __ASM_EMIT("mov         (%[rb], %[tmp1]), %%ah")
            __ASM_EMIT("mov         (%[rb], %[tmp2]), %%al")
            : [v] "+a"(v), [tmp1] "=&r"(tmp1), [tmp2] "=&r"(tmp2)
            : [rb] "r"(lsp_rb_data)
            : "cc"
        );
    #endif /* ARCH_X86_64 */

        return v;
    }

    inline uint16_t __lsp_forced_inline    reverse_bits(uint16_t v, size_t count)
    {
    #ifdef ARCH_X86_64
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("ror         $8, %%ax")
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("shr         %%cl, %[v]")

            : [v] "+a"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data), "c"(16 - count)
            : "cc"
        );
    #else
        size_t tmp1, tmp2;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp1]")
            __ASM_EMIT("movzx       %%ah, %[tmp2]")
            __ASM_EMIT("mov         (%[rb], %[tmp1]), %%ah")
            __ASM_EMIT("mov         (%[rb], %[tmp2]), %%al")
            __ASM_EMIT("shr         %%cl, %[v]")
            : [v] "+a"(v), [tmp1] "=&r"(tmp1), [tmp2] "=&r"(tmp2)
            : [rb] "r"(lsp_rb_data), "c"(16 - count)
            : "cc"
        );
    #endif /* ARCH_X86_64 */

        return v;
    }

    inline int16_t __lsp_forced_inline    reverse_bits(int16_t v, size_t count)
    {
    #ifdef ARCH_X86_64
        size_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("ror         $8, %%ax")
            __ASM_EMIT("movzx       %%al, %[tmp]")
            __ASM_EMIT("mov         (%[rb], %[tmp]), %%al")
            __ASM_EMIT("shr         %%cl, %[v]")

            : [v] "+a"(v), [tmp] "=&r"(tmp)
            : [rb] "r"(lsp_rb_data), "c"(16 - count)
            : "cc"
        );
    #else
        size_t tmp1, tmp2;

        ARCH_X86_ASM (
            __ASM_EMIT("movzx       %%al, %[tmp1]")
            __ASM_EMIT("movzx       %%ah, %[tmp2]")
            __ASM_EMIT("mov         (%[rb], %[tmp1]), %%ah")
            __ASM_EMIT("mov         (%[rb], %[tmp2]), %%al")
            __ASM_EMIT("shr         %%cl, %[v]")
            : [v] "+a"(v), [tmp1] "=&r"(tmp1), [tmp2] "=&r"(tmp2)
            : [rb] "r"(lsp_rb_data), "c"(16 - count)
            : "cc"
        );
    #endif /* ARCH_X86_64 */

        return v;
    }

    inline uint32_t __lsp_forced_inline    reverse_bits(uint32_t v)
    {
        uint32_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("bswap       %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xf0f0f0f0, %[v]")
            __ASM_EMIT("and         $0x0f0f0f0f, %[tmp]")
            __ASM_EMIT("shr         $4, %[v]")
            __ASM_EMIT("shl         $4, %[tmp]")
            __ASM_EMIT("or          %[tmp], %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xcccccccc, %[v]")
            __ASM_EMIT("and         $0x33333333, %[tmp]")
            __ASM_EMIT("shr         $2, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 4), %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xaaaaaaaa, %[v]")
            __ASM_EMIT("and         $0x55555555, %[tmp]")
            __ASM_EMIT("shr         $1, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 2), %[v]")

            : [v] "+r"(v), [tmp] "=&r" (tmp)
            :
            : "cc"
        );
        return v;
    }

    inline int32_t __lsp_forced_inline    reverse_bits(int32_t v)
    {
        uint32_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("bswap       %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xf0f0f0f0, %[v]")
            __ASM_EMIT("and         $0x0f0f0f0f, %[tmp]")
            __ASM_EMIT("shr         $4, %[v]")
            __ASM_EMIT("shl         $4, %[tmp]")
            __ASM_EMIT("or          %[tmp], %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xcccccccc, %[v]")
            __ASM_EMIT("and         $0x33333333, %[tmp]")
            __ASM_EMIT("shr         $2, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 4), %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xaaaaaaaa, %[v]")
            __ASM_EMIT("and         $0x55555555, %[tmp]")
            __ASM_EMIT("shr         $1, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 2), %[v]")

            : [v] "+r"(v), [tmp] "=&r" (tmp)
            :
            : "cc"
        );
        return v;
    }

    inline uint32_t __lsp_forced_inline    reverse_bits(uint32_t v, size_t count)
    {
        uint32_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("bswap       %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xf0f0f0f0, %[v]")
            __ASM_EMIT("and         $0x0f0f0f0f, %[tmp]")
            __ASM_EMIT("shr         $4, %[v]")
            __ASM_EMIT("shl         $4, %[tmp]")
            __ASM_EMIT("or          %[tmp], %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xcccccccc, %[v]")
            __ASM_EMIT("and         $0x33333333, %[tmp]")
            __ASM_EMIT("shr         $2, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 4), %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xaaaaaaaa, %[v]")
            __ASM_EMIT("and         $0x55555555, %[tmp]")
            __ASM_EMIT("shr         $1, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 2), %[v]")

            __ASM_EMIT("shr         %%cl, %[v]")

            : [v] "+r"(v), [tmp] "=&r" (tmp)
            : "c" (32-count)
            : "cc"
        );
        return v;
    }

    inline int32_t __lsp_forced_inline    reverse_bits(int32_t v, size_t count)
    {
        uint32_t tmp;

        ARCH_X86_ASM (
            __ASM_EMIT("bswap       %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xf0f0f0f0, %[v]")
            __ASM_EMIT("and         $0x0f0f0f0f, %[tmp]")
            __ASM_EMIT("shr         $4, %[v]")
            __ASM_EMIT("shl         $4, %[tmp]")
            __ASM_EMIT("or          %[tmp], %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xcccccccc, %[v]")
            __ASM_EMIT("and         $0x33333333, %[tmp]")
            __ASM_EMIT("shr         $2, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 4), %[v]")

            __ASM_EMIT("mov         %[v], %[tmp]")
            __ASM_EMIT("and         $0xaaaaaaaa, %[v]")
            __ASM_EMIT("and         $0x55555555, %[tmp]")
            __ASM_EMIT("shr         $1, %[v]")
            __ASM_EMIT("lea         (%[v], %[tmp], 2), %[v]")

            __ASM_EMIT("shr         %%cl, %[v]")

            : [v] "+r"(v), [tmp] "=&r" (tmp)
            : "c" (32-count)
            : "cc"
        );
        return v;
    }

    #ifdef ARCH_I386
        inline uint64_t __lsp_forced_inline    reverse_bits(uint64_t v)
        {
            uint32_t tmp1, tmp2;

            ARCH_X86_ASM
            (
                __ASM_EMIT("bswap %%eax")
                __ASM_EMIT("bswap %%edx")
                __ASM_EMIT("xchg %%edx, %%eax")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                __ASM_EMIT("and $0xf0f0f0f0, %%edx")
                __ASM_EMIT("and $0x0f0f0f0f, %1")
                __ASM_EMIT("and $0x0f0f0f0f, %2")
                __ASM_EMIT("shr $4, %%eax")
                __ASM_EMIT("shr $4, %%edx")
                __ASM_EMIT("shl $4, %1")
                __ASM_EMIT("shl $4, %2")
                __ASM_EMIT("or  %1, %%eax")
                __ASM_EMIT("or  %2, %%edx")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xcccccccc, %%eax")
                __ASM_EMIT("and $0xcccccccc, %%edx")
                __ASM_EMIT("and $0x33333333, %1")
                __ASM_EMIT("and $0x33333333, %2")
                __ASM_EMIT("shr $2, %%eax")
                __ASM_EMIT("shr $2, %%edx")
                __ASM_EMIT("lea (%%eax, %1, 4), %%eax")
                __ASM_EMIT("lea (%%edx, %2, 4), %%edx")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                __ASM_EMIT("and $0xaaaaaaaa, %%edx")
                __ASM_EMIT("and $0x55555555, %1")
                __ASM_EMIT("and $0x55555555, %2")
                __ASM_EMIT("shr $1, %%eax")
                __ASM_EMIT("shr $1, %%edx")
                __ASM_EMIT("lea (%%eax, %1, 2), %%eax")
                __ASM_EMIT("lea (%%edx, %2, 2), %%edx")

                : "+A"(v), "=&r"(tmp1), "=&r"(tmp2)
                :
                : "cc"
            );

            return v;
        }

        inline int64_t __lsp_forced_inline    reverse_bits(int64_t v)
        {
            uint32_t tmp1, tmp2;

            ARCH_X86_ASM
            (
                __ASM_EMIT("bswap %%eax")
                __ASM_EMIT("bswap %%edx")
                __ASM_EMIT("xchg %%edx, %%eax")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                __ASM_EMIT("and $0xf0f0f0f0, %%edx")
                __ASM_EMIT("and $0x0f0f0f0f, %1")
                __ASM_EMIT("and $0x0f0f0f0f, %2")
                __ASM_EMIT("shr $4, %%eax")
                __ASM_EMIT("shr $4, %%edx")
                __ASM_EMIT("shl $4, %1")
                __ASM_EMIT("shl $4, %2")
                __ASM_EMIT("or  %1, %%eax")
                __ASM_EMIT("or  %2, %%edx")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xcccccccc, %%eax")
                __ASM_EMIT("and $0xcccccccc, %%edx")
                __ASM_EMIT("and $0x33333333, %1")
                __ASM_EMIT("and $0x33333333, %2")
                __ASM_EMIT("shr $2, %%eax")
                __ASM_EMIT("shr $2, %%edx")
                __ASM_EMIT("lea (%%eax, %1, 4), %%eax")
                __ASM_EMIT("lea (%%edx, %2, 4), %%edx")

                __ASM_EMIT("mov %%eax, %1")
                __ASM_EMIT("mov %%edx, %2")
                __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                __ASM_EMIT("and $0xaaaaaaaa, %%edx")
                __ASM_EMIT("and $0x55555555, %1")
                __ASM_EMIT("and $0x55555555, %2")
                __ASM_EMIT("shr $1, %%eax")
                __ASM_EMIT("shr $1, %%edx")
                __ASM_EMIT("lea (%%eax, %1, 2), %%eax")
                __ASM_EMIT("lea (%%edx, %2, 2), %%edx")

                : "+A"(v), "=&r"(tmp1), "=&r"(tmp2)
                :
                : "cc"
            );

            return v;
        }

        inline uint64_t __lsp_forced_inline    reverse_bits(uint64_t v, size_t count)
        {
            uint32_t tmp1, tmp2;
            count = 64 - count;

            if (count < 32)
            {
                ARCH_X86_ASM
                (
                    __ASM_EMIT("bswap %%eax")
                    __ASM_EMIT("bswap %%edx")
                    __ASM_EMIT("xchg %%edx, %%eax")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                    __ASM_EMIT("and $0xf0f0f0f0, %%edx")
                    __ASM_EMIT("and $0x0f0f0f0f, %[t1]")
                    __ASM_EMIT("and $0x0f0f0f0f, %[t2]")
                    __ASM_EMIT("shr $4, %%eax")
                    __ASM_EMIT("shr $4, %%edx")
                    __ASM_EMIT("shl $4, %[t1]")
                    __ASM_EMIT("shl $4, %[t2]")
                    __ASM_EMIT("or  %[t1], %%eax")
                    __ASM_EMIT("or  %[t2], %%edx")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xcccccccc, %%eax")
                    __ASM_EMIT("and $0xcccccccc, %%edx")
                    __ASM_EMIT("and $0x33333333, %[t1]")
                    __ASM_EMIT("and $0x33333333, %[t2]")
                    __ASM_EMIT("shr $2, %%eax")
                    __ASM_EMIT("shr $2, %%edx")
                    __ASM_EMIT("lea (%%eax, %[t1], 4), %%eax")
                    __ASM_EMIT("lea (%%edx, %[t2], 4), %%edx")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                    __ASM_EMIT("and $0xaaaaaaaa, %%edx")
                    __ASM_EMIT("and $0x55555555, %[t1]")
                    __ASM_EMIT("and $0x55555555, %[t2]")
                    __ASM_EMIT("shr $1, %%eax")
                    __ASM_EMIT("shr $1, %%edx")
                    __ASM_EMIT("lea (%%eax, %[t1], 2), %%eax")
                    __ASM_EMIT("lea (%%edx, %[t2], 2), %%edx")

                    __ASM_EMIT("shrd %%cl, %%edx, %%eax")
                    __ASM_EMIT("shr %%cl, %%edx")

                    : [v] "+A"(v), [t1] "=&r"(tmp1), [t2] "=&r"(tmp2)
                    : [c] "c" (count)
                    : "cc"
                );
            }
            else
            {
                ARCH_X86_ASM
                (
                    __ASM_EMIT("bswap %%eax")
                    __ASM_EMIT("sub $32, %[c]")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                    __ASM_EMIT("and $0x0f0f0f0f, %%edx")
                    __ASM_EMIT("shr $4, %%eax")
                    __ASM_EMIT("shl $4, %%edx")
                    __ASM_EMIT("or  %%edx, %%eax")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xcccccccc, %%eax")
                    __ASM_EMIT("and $0x33333333, %%edx")
                    __ASM_EMIT("shr $2, %%eax")
                    __ASM_EMIT("lea (%%eax, %%edx, 4), %%eax")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                    __ASM_EMIT("and $0x55555555, %%edx")
                    __ASM_EMIT("shr $1, %%eax")
                    __ASM_EMIT("lea (%%eax, %%edx, 2), %%eax")

                    __ASM_EMIT("xor %%edx, %%edx")
                    __ASM_EMIT("shr %%cl, %%eax")

                    : [v] "+A"(v), [c] "+c" (count)
                    :
                    : "cc"
                );
            }

            return v;
        }

        inline int64_t __lsp_forced_inline    reverse_bits(int64_t v, size_t count)
        {
            uint32_t tmp1, tmp2;
            count = 64 - count;

            if (count < 32)
            {
                ARCH_X86_ASM
                (
                    __ASM_EMIT("bswap %%eax")
                    __ASM_EMIT("bswap %%edx")
                    __ASM_EMIT("xchg %%edx, %%eax")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                    __ASM_EMIT("and $0xf0f0f0f0, %%edx")
                    __ASM_EMIT("and $0x0f0f0f0f, %[t1]")
                    __ASM_EMIT("and $0x0f0f0f0f, %[t2]")
                    __ASM_EMIT("shr $4, %%eax")
                    __ASM_EMIT("shr $4, %%edx")
                    __ASM_EMIT("shl $4, %[t1]")
                    __ASM_EMIT("shl $4, %[t2]")
                    __ASM_EMIT("or  %[t1], %%eax")
                    __ASM_EMIT("or  %[t2], %%edx")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xcccccccc, %%eax")
                    __ASM_EMIT("and $0xcccccccc, %%edx")
                    __ASM_EMIT("and $0x33333333, %[t1]")
                    __ASM_EMIT("and $0x33333333, %[t2]")
                    __ASM_EMIT("shr $2, %%eax")
                    __ASM_EMIT("shr $2, %%edx")
                    __ASM_EMIT("lea (%%eax, %[t1], 4), %%eax")
                    __ASM_EMIT("lea (%%edx, %[t2], 4), %%edx")

                    __ASM_EMIT("mov %%eax, %[t1]")
                    __ASM_EMIT("mov %%edx, %[t2]")
                    __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                    __ASM_EMIT("and $0xaaaaaaaa, %%edx")
                    __ASM_EMIT("and $0x55555555, %[t1]")
                    __ASM_EMIT("and $0x55555555, %[t2]")
                    __ASM_EMIT("shr $1, %%eax")
                    __ASM_EMIT("shr $1, %%edx")
                    __ASM_EMIT("lea (%%eax, %[t1], 2), %%eax")
                    __ASM_EMIT("lea (%%edx, %[t2], 2), %%edx")

                    __ASM_EMIT("shrd %%cl, %%edx, %%eax")
                    __ASM_EMIT("shr %%cl, %%edx")

                    : [v] "+A"(v), [t1] "=&r"(tmp1), [t2] "=&r"(tmp2)
                    : [c] "c" (count)
                    : "cc"
                );
            }
            else
            {
                ARCH_X86_ASM
                (
                    __ASM_EMIT("bswap %%eax")
                    __ASM_EMIT("sub $32, %[c]")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xf0f0f0f0, %%eax")
                    __ASM_EMIT("and $0x0f0f0f0f, %%edx")
                    __ASM_EMIT("shr $4, %%eax")
                    __ASM_EMIT("shl $4, %%edx")
                    __ASM_EMIT("or  %%edx, %%eax")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xcccccccc, %%eax")
                    __ASM_EMIT("and $0x33333333, %%edx")
                    __ASM_EMIT("shr $2, %%eax")
                    __ASM_EMIT("lea (%%eax, %%edx, 4), %%eax")

                    __ASM_EMIT("mov %%eax, %%edx")
                    __ASM_EMIT("and $0xaaaaaaaa, %%eax")
                    __ASM_EMIT("and $0x55555555, %%edx")
                    __ASM_EMIT("shr $1, %%eax")
                    __ASM_EMIT("lea (%%eax, %%edx, 2), %%eax")

                    __ASM_EMIT("xor %%edx, %%edx")
                    __ASM_EMIT("shr %%cl, %%eax")

                    : [v] "+A"(v), [c] "+c" (count)
                    :
                    : "cc"
                );
            }

            return v;
        }
    #else /* ARCH_X86_64 */
        inline uint64_t __lsp_forced_inline    reverse_bits(uint64_t v)
        {
            uint64_t tmp;

            ARCH_X86_64_ASM (
                __ASM_EMIT("bswap       %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask1], %[tmp]")
                __ASM_EMIT("shr         $4, %[v]")
                __ASM_EMIT("shl         $4, %[tmp]")
                __ASM_EMIT("and         %[mask1], %[v]")
                __ASM_EMIT("or          %[tmp], %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask2], %[tmp]")
                __ASM_EMIT("shr         $2, %[v]")
                __ASM_EMIT("and         %[mask2], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],4), %[v]")     // v = v | (tmp << 2)

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask3], %[tmp]")
                __ASM_EMIT("shr         $1, %[v]")
                __ASM_EMIT("and         %[mask3], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],2), %[v]")     // v = v | (tmp << 1)

                : [v] "+r"(v), [tmp] "=&r"(tmp)
                :
                  [mask1] "r" (0x0f0f0f0f0f0f0f0fULL),
                  [mask2] "r" (0x3333333333333333ULL),
                  [mask3] "r" (0x5555555555555555ULL)
                : "cc"
            );

            return v;
        }

        inline int64_t __lsp_forced_inline    reverse_bits(int64_t v)
        {
            uint64_t tmp;

            ARCH_X86_64_ASM (
                __ASM_EMIT("bswap       %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask1], %[tmp]")
                __ASM_EMIT("shr         $4, %[v]")
                __ASM_EMIT("shl         $4, %[tmp]")
                __ASM_EMIT("and         %[mask1], %[v]")
                __ASM_EMIT("or          %[tmp], %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask2], %[tmp]")
                __ASM_EMIT("shr         $2, %[v]")
                __ASM_EMIT("and         %[mask2], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],4), %[v]")     // v = v | (tmp << 2)

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask3], %[tmp]")
                __ASM_EMIT("shr         $1, %[v]")
                __ASM_EMIT("and         %[mask3], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],2), %[v]")     // v = v | (tmp << 1)

                : [v] "+r"(v), [tmp] "=&r"(tmp)
                :
                  [mask1] "r" (0x0f0f0f0f0f0f0f0fULL),
                  [mask2] "r" (0x3333333333333333ULL),
                  [mask3] "r" (0x5555555555555555ULL)
                : "cc"
            );

            return v;
        }

        inline uint64_t __lsp_forced_inline    reverse_bits(uint64_t v, size_t count)
        {
            uint64_t tmp;

            ARCH_X86_64_ASM (
                __ASM_EMIT("bswap       %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask1], %[tmp]")
                __ASM_EMIT("shr         $4, %[v]")
                __ASM_EMIT("shl         $4, %[tmp]")
                __ASM_EMIT("and         %[mask1], %[v]")
                __ASM_EMIT("or          %[tmp], %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask2], %[tmp]")
                __ASM_EMIT("shr         $2, %[v]")
                __ASM_EMIT("and         %[mask2], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],4), %[v]")     // v = v | (tmp << 2)

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask3], %[tmp]")
                __ASM_EMIT("shr         $1, %[v]")
                __ASM_EMIT("and         %[mask3], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],2), %[v]")     // v = v | (tmp << 1)

                __ASM_EMIT("shr %%cl, %[v]")

                : [v] "+r"(v), [tmp] "=&r"(tmp)
                :
                  [mask1] "r" (0x0f0f0f0f0f0f0f0fULL),
                  [mask2] "r" (0x3333333333333333ULL),
                  [mask3] "r" (0x5555555555555555ULL),
                  "c" (64-count)
                : "cc"
            );

            return v;
        }

        inline int64_t __lsp_forced_inline    reverse_bits(int64_t v, size_t count)
        {
            uint64_t tmp;

            ARCH_X86_64_ASM (
                __ASM_EMIT("bswap       %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask1], %[tmp]")
                __ASM_EMIT("shr         $4, %[v]")
                __ASM_EMIT("shl         $4, %[tmp]")
                __ASM_EMIT("and         %[mask1], %[v]")
                __ASM_EMIT("or          %[tmp], %[v]")

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask2], %[tmp]")
                __ASM_EMIT("shr         $2, %[v]")
                __ASM_EMIT("and         %[mask2], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],4), %[v]")     // v = v | (tmp << 2)

                __ASM_EMIT("mov         %[v], %[tmp]")
                __ASM_EMIT("and         %[mask3], %[tmp]")
                __ASM_EMIT("shr         $1, %[v]")
                __ASM_EMIT("and         %[mask3], %[v]")
                __ASM_EMIT("lea         (%[v],%[tmp],2), %[v]")     // v = v | (tmp << 1)

                __ASM_EMIT("shr %%cl, %[v]")

                : [v] "+r"(v), [tmp] "=&r"(tmp)
                :
                  [mask1] "r" (0x0f0f0f0f0f0f0f0fULL),
                  [mask2] "r" (0x3333333333333333ULL),
                  [mask3] "r" (0x5555555555555555ULL),
                  "c" (64-count)
                : "cc"
            );

            return v;
        }

    #endif /* ARCH_I386 */

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_X86_BITS_REVERSE_H_ */
