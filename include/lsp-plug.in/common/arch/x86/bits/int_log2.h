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

#ifndef LSP_PLUG_IN_COMMON_ARCH_X86_BITS_H_
#define LSP_PLUG_IN_COMMON_ARCH_X86_BITS_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline int __lsp_forced_inline int_log2(uint8_t v)
    {
        uint32_t res = v;

        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (res)
            : [tmp] "r" (0)
            : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int8_t v)
    {
        uint32_t res = uint8_t(v);

        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (res)
            : [tmp] "r" (0)
            : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint16_t v)
    {
        uint32_t res = v;

        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (res)
            : [tmp] "r" (0)
            : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int16_t v)
    {
        uint32_t res = uint16_t(v);

        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (res)
            : [tmp] "r" (0)
            : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint32_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (v)
            : [tmp] "r" (0)
            : "cc"
        );
        return v;
    }

    inline int __lsp_forced_inline     int_log2(int32_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %[tmp], %[res]")
            : [res] "+r" (v)
            : [tmp] "r" (0)
            : "cc"
        );
        return v;
    }

#ifdef ARCH_X86_64
    inline int __lsp_forced_inline     int_log2(uint64_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %q[tmp], %[res]")
            : [res] "+r" (v)
            : [tmp] "r" (0)
            : "cc"
        );
        return int(v);
    }

    inline int __lsp_forced_inline     int_log2(int64_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("bsr         %[res], %[res]")
            __ASM_EMIT("cmovz       %q[tmp], %[res]")
            : [res] "+r" (v)
            : [tmp] "r" (0)
            : "cc"
        );
        return int(v);
    }
#else
    inline int __lsp_forced_inline     int_log2(uint64_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("test    %%edx, %%edx")
            __ASM_EMIT("jz      2f")
            __ASM_EMIT("mov     %%edx, %%eax")
            __ASM_EMIT("xor     %%edx, %%edx")
            __ASM_EMIT("bsr     %%eax, %%eax")
            __ASM_EMIT("cmovz   %%edx, %%eax")
            __ASM_EMIT("add     $32, %%eax")
            __ASM_EMIT("jmp     4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("xor     %%edx, %%edx")
            __ASM_EMIT("bsr     %%eax, %%eax")
            __ASM_EMIT("cmovz   %%edx, %%eax")

            __ASM_EMIT("4:")

            : [v] "+A" (v)
            :
            : "cc"
        );
        return int(v);
    }

    inline int __lsp_forced_inline     int_log2(int64_t v)
    {
        ARCH_X86_ASM (
            __ASM_EMIT("test    %%edx, %%edx")
            __ASM_EMIT("jz      2f")
            __ASM_EMIT("mov     %%edx, %%eax")
            __ASM_EMIT("xor     %%edx, %%edx")
            __ASM_EMIT("bsr     %%eax, %%eax")
            __ASM_EMIT("cmovz   %%edx, %%eax")
            __ASM_EMIT("add     $32, %%eax")
            __ASM_EMIT("jmp     4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("xor     %%edx, %%edx")
            __ASM_EMIT("bsr     %%eax, %%eax")
            __ASM_EMIT("cmovz   %%edx, %%eax")

            __ASM_EMIT("4:")

            : [v] "+A" (v)
            :
            : "cc"
        );
        return int(v);
    }
#endif /* ARCH_X86_64 */

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_X86_BITS_H_ */
