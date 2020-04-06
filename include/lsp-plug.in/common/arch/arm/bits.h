/*
 * bits.h
 *
 *  Created on: 1 апр. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

#ifdef ARCH_ARM7
    #include <lsp-plug.in/common/arch/arm/armv7/bits.h>
#else
    #include <lsp-plug.in/common/arch/arm/armv6/bits.h>
#endif

namespace lsp
{
    inline int __lsp_forced_inline     int_log2(uint8_t v)
    {
        int res = v;
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int8_t v)
    {
        int res = uint8_t(v);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint16_t v)
    {
        int res = v;
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int16_t v)
    {
        int res = uint16_t(v);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint32_t v)
    {
        int res = int(v);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int32_t v)
    {
        int res = int(v);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[res], %[res]")
            __ASM_EMIT("clzne           %[res], %[res]")
            __ASM_EMIT("rsbne           %[res], %[res], $31")
            : [res] "+r" (res)
            : : "cc"
        );
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint64_t v)
    {
        int hi = int(v >> 32);
        int lo = int(v & 0xffffffff);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[hi], %[hi]")
            __ASM_EMIT("beq             2f")
            __ASM_EMIT("clzne           %[lo], %[hi]")
            __ASM_EMIT("rsbne           %[lo], %[lo], $63")
            __ASM_EMIT("b               4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("tst             %[lo], %[lo]")
            __ASM_EMIT("clzne           %[lo], %[lo]")
            __ASM_EMIT("rsbne           %[lo], %[lo], $31")

            __ASM_EMIT("4:")
            : [lo] "+r" (lo)
            : [hi] "r" (hi)
            : "cc"
        );
        return lo;
    }

    inline int __lsp_forced_inline     int_log2(int64_t v)
    {
        int hi = int(uint64_t(v) >> 32);
        int lo = int(v & 0xffffffff);
        ARCH_ARM_ASM
        (
            __ASM_EMIT("tst             %[hi], %[hi]")
            __ASM_EMIT("beq             2f")
            __ASM_EMIT("clzne           %[lo], %[hi]")
            __ASM_EMIT("rsbne           %[lo], %[lo], $63")
            __ASM_EMIT("b               4f")

            __ASM_EMIT("2:")
            __ASM_EMIT("tst             %[lo], %[lo]")
            __ASM_EMIT("clzne           %[lo], %[lo]")
            __ASM_EMIT("rsbne           %[lo], %[lo], $31")

            __ASM_EMIT("4:")
            : [lo] "+r" (lo)
            : [hi] "r" (hi)
            : "cc"
        );
        return lo;
    }
}

#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_BITS_H_ */
