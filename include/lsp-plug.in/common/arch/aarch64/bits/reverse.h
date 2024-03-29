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

#ifndef LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_REVERSE_H_
#define LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_REVERSE_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline uint64_t reverse_bits(uint64_t src)
    {
        uint64_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint64_t reverse_bits(uint64_t src, size_t count)
    {
        uint64_t res, tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int64_t reverse_bits(int64_t src)
    {
        int64_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int64_t reverse_bits(int64_t src, size_t count)
    {
        int64_t res, tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint32_t reverse_bits(uint32_t src)
    {
        uint32_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %w[res], %w[src]")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint32_t reverse_bits(uint32_t src, size_t count)
    {
        uint32_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int32_t reverse_bits(int32_t src)
    {
        int32_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %w[res], %w[src]")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int32_t reverse_bits(int32_t src, size_t count)
    {
        int32_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint16_t reverse_bits(uint16_t src)
    {
        uint16_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("lsr     %x[res], %x[res], #48")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint16_t reverse_bits(uint16_t src, size_t count)
    {
        uint16_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int16_t reverse_bits(int16_t src)
    {
        int16_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("lsr     %x[res], %x[res], #48")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int16_t reverse_bits(int16_t src, size_t count)
    {
        int16_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint8_t reverse_bits(uint8_t src)
    {
        uint8_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("lsr     %x[res], %x[res], #56")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline uint8_t reverse_bits(uint8_t src, size_t count)
    {
        uint8_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int8_t reverse_bits(int8_t src)
    {
        int8_t res;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("lsr     %x[res], %x[res], #56")
            : [res] "=r" (res)
            : [src] "r" (src)
            :
        );

        return res;
    }

    inline int8_t reverse_bits(int8_t src, size_t count)
    {
        int8_t res;
        uint64_t tmp;

        ARCH_AARCH64_ASM (
            __ASM_EMIT("rbit    %x[res], %x[src]")
            __ASM_EMIT("mov     %x[tmp], #64")
            __ASM_EMIT("sub     %x[count], %x[tmp], %x[count]")
            __ASM_EMIT("lsr     %x[res], %x[res], %x[count]")
            : [res] "=r" (res), [count] "+r" (count), [tmp] "=&r" (tmp)
            : [src] "r" (src)
            :
        );

        return res;
    }

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_AARCH64_BITS_REVERSE_H_ */
