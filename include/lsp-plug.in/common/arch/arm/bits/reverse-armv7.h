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

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV7_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV7_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline uint32_t reverse_bits(uint32_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            : [src] "+r" (src)
            : :
        );

        return src;
    }

    inline uint32_t reverse_bits(uint32_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline int32_t reverse_bits(int32_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            : [src] "+r" (src)
            :
        );

        return src;
    }

    inline int32_t reverse_bits(int32_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline uint16_t reverse_bits(uint16_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], #16")
            : [src] "+r" (src)
            : :
        );

        return src;
    }

    inline uint16_t reverse_bits(uint16_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline int16_t reverse_bits(int16_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], #16")
            : [src] "+r" (src)
            : :
        );

        return src;
    }

    inline int16_t reverse_bits(int16_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline uint8_t reverse_bits(uint8_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], #24")
            : [src] "+r" (src)
            : :
        );

        return src;
    }

    inline uint8_t reverse_bits(uint8_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline int8_t reverse_bits(int8_t src)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], #24")
            : [src] "+r" (src)
            : :
        );

        return src;
    }

    inline int8_t reverse_bits(int8_t src, size_t count)
    {
        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            __ASM_EMIT("rbit    %[src], %[src]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count)
            : :
        );

        return src;
    }

    inline uint64_t reverse_bits(uint64_t v)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rbit            %[lo], %[lo]")
            __ASM_EMIT("rbit            %[hi], %[hi]")
            : [lo] "+r" (lo), [hi] "+r" (hi)
            : :
        );

        return hi | (uint64_t(lo) << 32);
    }

    inline int64_t reverse_bits(int64_t v)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rbit            %[lo], %[lo]")
            __ASM_EMIT("rbit            %[hi], %[hi]")
            : [lo] "+r" (lo), [hi] "+r" (hi)
            : :
        );

        return hi | (int64_t(lo) << 32);
    }

    inline uint64_t reverse_bits(uint64_t v, size_t count)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t tmp;

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rsb             %[count], %[count], #64")
            __ASM_EMIT("rbit            %[lo], %[lo]")
            __ASM_EMIT("rbit            %[hi], %[hi]")                  // [ lo, hi ]
            __ASM_EMIT("cmp             %[count], #32")
            __ASM_EMIT("blo             2f")

            __ASM_EMIT("mov             %[hi], %[lo]")                  // [ lo, lo ]
            __ASM_EMIT("sub             %[count], #32")
            __ASM_EMIT("eor             %[lo], %[lo]")                  // [ 0, lo ]
            __ASM_EMIT("lsr             %[hi], %[count]")               // [ 0, lo >> count ]
            __ASM_EMIT("b               4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("rsb             %[tmp], %[count], #32")         // tmp = (32 - count)
            __ASM_EMIT("lsr             %[hi], %[count]")               // [ lo, hi >> count ]
            __ASM_EMIT("lsl             %[tmp], %[lo], %[tmp]")         // tmp = lo << (32 - count)
            __ASM_EMIT("lsr             %[lo], %[count]")               // lo >> (32 - count)
            __ASM_EMIT("orr             %[hi], %[tmp]")                 // [ lo >> count, (hi >> count) | (lo << (32 - count)) ]

            __ASM_EMIT("4:")
            : [lo] "+r" (lo), [hi] "+r" (hi), [tmp] "=&r" (tmp),
              [count] "+r" (count)
            : :
        );

        return hi | (uint64_t(lo) << 32);
    }

    inline int64_t reverse_bits(int64_t v, size_t count)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t tmp;

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rsb             %[count], %[count], #64")
            __ASM_EMIT("rbit            %[lo], %[lo]")
            __ASM_EMIT("rbit            %[hi], %[hi]")                  // [ lo, hi ]
            __ASM_EMIT("cmp             %[count], #32")
            __ASM_EMIT("blo             2f")

            __ASM_EMIT("mov             %[hi], %[lo]")                  // [ lo, lo ]
            __ASM_EMIT("sub             %[count], #32")
            __ASM_EMIT("eor             %[lo], %[lo]")                  // [ 0, lo ]
            __ASM_EMIT("lsr             %[hi], %[count]")               // [ 0, lo >> count ]
            __ASM_EMIT("b               4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("rsb             %[tmp], %[count], #32")         // tmp = (32 - count)
            __ASM_EMIT("lsr             %[hi], %[count]")               // [ lo, hi >> count ]
            __ASM_EMIT("lsl             %[tmp], %[lo], %[tmp]")         // tmp = lo << (32 - count)
            __ASM_EMIT("lsr             %[lo], %[count]")               // lo >> (32 - count)
            __ASM_EMIT("orr             %[hi], %[tmp]")                 // [ lo >> count, (hi >> count) | (lo << (32 - count)) ]

            __ASM_EMIT("4:")
            : [lo] "+r" (lo), [hi] "+r" (hi), [tmp] "=&r" (tmp),
              [count] "+r" (count)
            : :
        );

        return hi | (int64_t(lo) << 32);
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV7_H_ */
