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

#ifndef LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_INT_LOG2_H_
#define LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_INT_LOG2_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline int __lsp_forced_inline     int_log2(uint8_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int8_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint16_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int16_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint32_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int32_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %w[res], %w[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %w[res], %w[v]")
            __ASM_EMIT("mov             %w[v], #31")
            __ASM_EMIT("sub             %w[res], %w[v], %w[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint64_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %x[res], %x[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %x[res], %x[v]")
            __ASM_EMIT("mov             %x[v], #63")
            __ASM_EMIT("sub             %x[res], %x[v], %x[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int64_t v)
    {
        int32_t res;
        ARCH_AARCH64_ASM (
            __ASM_EMIT("subs            %x[res], %x[v], #0")    // res = v
            __ASM_EMIT("b.eq            1f")                    // res == 0?
            __ASM_EMIT("clz             %x[res], %x[v]")
            __ASM_EMIT("mov             %x[v], #63")
            __ASM_EMIT("sub             %x[res], %x[v], %x[res]")
            __ASM_EMIT("1:")
            : [res] "=r" (res), [v] "+r" (v)
            : : "cc"
        );
        return res;
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_INT_LOG2_H_ */
