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

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV6_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV6_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    #define LSP_ARMV6_MV_RBIT32(dst, src, msk, tmp, masks) \
        __ASM_EMIT("rev     " dst ", " src ) \
        /* round 1 */ \
        __ASM_EMIT("ldr     " msk ", [" masks ", #0]") \
        __ASM_EMIT("and     " tmp ", " msk ", " dst ", lsr #1") \
        __ASM_EMIT("and     " msk ", " msk ", " dst) \
        __ASM_EMIT("orr     " dst ", " tmp ", " msk ", lsl #1") \
        /* round 2 */ \
        __ASM_EMIT("ldr     " msk ", [" masks ", #4]") \
        __ASM_EMIT("and     " tmp ", " msk ", " dst ", lsr #2") \
        __ASM_EMIT("and     " msk ", " msk ", " dst) \
        __ASM_EMIT("orr     " dst ", " tmp ", " msk ", lsl #2") \
        /* round 3 */ \
        __ASM_EMIT("ldr     " msk ", [" masks ", #8]") \
        __ASM_EMIT("and     " tmp ", " msk ", " dst ", lsr #4") \
        __ASM_EMIT("and     " msk ", " msk ", " dst) \
        __ASM_EMIT("orr     " dst ", " tmp ", " msk ", lsl #4") \

    #define LSP_ARMV6_RBIT32(dst, msk, tmp, masks)      LSP_ARMV6_MV_RBIT32(dst, dst, msk, tmp, masks)

    extern const uint32_t lsp_rb_masks[];

    inline uint32_t reverse_bits(uint32_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }


    inline uint32_t reverse_bits(uint32_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline int32_t reverse_bits(int32_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline int32_t reverse_bits(int32_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline uint16_t reverse_bits(uint16_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr %[src], #16")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline uint16_t reverse_bits(uint16_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline int16_t reverse_bits(int16_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr %[src], #16")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline int16_t reverse_bits(int16_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline uint8_t reverse_bits(uint8_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr %[src], #24")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline uint8_t reverse_bits(uint8_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline int8_t reverse_bits(int8_t src)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr %[src], #24")
            : [src] "+r" (src),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
        );

        return src;
    }

    inline int8_t reverse_bits(int8_t src, size_t count)
    {
        uint32_t msk, tmp;

        ARCH_ARM_ASM (
            __ASM_EMIT("rsb     %[count], %[count], #32")
            LSP_ARMV6_RBIT32("%[src]", "%[msk]", "%[tmp]", "%[masks]")
            __ASM_EMIT("lsr     %[src], %[count]")
            : [src] "+r" (src), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return src;
    }

    inline uint64_t reverse_bits(uint64_t v)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t msk, tmp;

        ARCH_ARM_ASM
        (
            LSP_ARMV6_RBIT32("%[lo]", "%[msk]", "%[tmp]", "%[masks]")
            LSP_ARMV6_RBIT32("%[hi]", "%[msk]", "%[tmp]", "%[masks]")
            : [lo] "+r" (lo), [hi] "+r" (hi),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return hi | (uint64_t(lo) << 32);
    }

    inline int64_t reverse_bits(int64_t v)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t msk, tmp;

        ARCH_ARM_ASM
        (
            LSP_ARMV6_RBIT32("%[lo]", "%[msk]", "%[tmp]", "%[masks]")
            LSP_ARMV6_RBIT32("%[hi]", "%[msk]", "%[tmp]", "%[masks]")
            : [lo] "+r" (lo), [hi] "+r" (hi),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return hi | (int64_t(lo) << 32);
    }

    inline uint64_t reverse_bits(uint64_t v, size_t count)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t msk, tmp;

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rsb             %[count], %[count], #64")
            LSP_ARMV6_RBIT32("%[lo]", "%[msk]", "%[tmp]", "%[masks]")
            LSP_ARMV6_RBIT32("%[hi]", "%[msk]", "%[tmp]", "%[masks]")
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
            : [lo] "+r" (lo), [hi] "+r" (hi), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return hi | (uint64_t(lo) << 32);
    }

    inline int64_t reverse_bits(int64_t v, size_t count)
    {
        uint32_t lo = uint32_t(v);
        uint32_t hi = uint32_t(v >> 32);
        uint32_t msk, tmp;

        ARCH_ARM_ASM
        (
            __ASM_EMIT("rsb             %[count], %[count], #64")
            LSP_ARMV6_RBIT32("%[lo]", "%[msk]", "%[tmp]", "%[masks]")
            LSP_ARMV6_RBIT32("%[hi]", "%[msk]", "%[tmp]", "%[masks]")
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
            : [lo] "+r" (lo), [hi] "+r" (hi), [count] "+r" (count),
              [msk] "=&r" (msk), [tmp] "=&r" (tmp)
            : [masks] "r" (lsp_rb_masks)
            :
        );

        return hi | (int64_t(lo) << 32);
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_REVERSE_ARMV6_H_ */
