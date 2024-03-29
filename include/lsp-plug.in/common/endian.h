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

#ifndef LSP_PLUG_IN_COMMON_ENDIAN_H_
#define LSP_PLUG_IN_COMMON_ENDIAN_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

#define LSP_PLUG_IN_COMMON_ENDIAN_IMPL
    // Include unsigned functions definition
    #if defined(ARCH_X86)
        #include <lsp-plug.in/common/arch/x86/endian.h>
    #elif defined(ARCH_AARCH64)
        #include <lsp-plug.in/common/arch/aarch64/endian.h>
    #elif defined(ARCH_ARM6)
        #include <lsp-plug.in/common/arch/arm/endian.h>
    #elif defined(ARCH_ARM7)
        #include <lsp-plug.in/common/arch/arm/endian.h>
    #else
        #include <lsp-plug.in/common/arch/generic/endian.h>
    #endif /* defined(ARCH_X86) */
#undef LSP_PLUG_IN_COMMON_ENDIAN_IMPL

// Define macros
#ifdef ARCH_LE
    #define LE_TO_CPU(x)            (x)
    #define CPU_TO_LE(x)            (x)

    #define BE_TO_CPU(x)            ::lsp::byte_swap(x)
    #define CPU_TO_BE(x)            ::lsp::byte_swap(x)

    #define VLE_TO_CPU(v, n)        do {} while(false)
    #define CPU_TO_VLE(v, n)        do {} while(false)

    #define VBE_TO_CPU(v, n)        ::lsp::byte_swap(v, n)
    #define CPU_TO_VBE(v, n)        ::lsp::byte_swap(v, n)

#else
    #define LE_TO_CPU(x)            ::lsp::byte_swap(x)
    #define CPU_TO_LE(x)            ::lsp::byte_swap(x)

    #define BE_TO_CPU(x)            (x)
    #define CPU_TO_BE(x)            (x)

    #define VLE_TO_CPU(v, n)        ::lsp::byte_swap(v, n)
    #define CPU_TO_VLE(v, n)        ::lsp::byte_swap(v, n)

    #define VBE_TO_CPU(v, n)        do {} while(false)
    #define CPU_TO_VBE(v, n)        do {} while(false)

#endif /* */

namespace lsp
{
    inline uint8_t __lsp_forced_inline    byte_swap(uint8_t v)
    {
        return v;
    }

    inline int8_t __lsp_forced_inline       byte_swap(int8_t v)
    {
        return v;
    }

    inline int16_t __lsp_forced_inline      byte_swap(int16_t v)
    {
        return byte_swap(uint16_t(v));
    }

    inline int32_t __lsp_forced_inline      byte_swap(int32_t v)
    {
        return byte_swap(uint32_t(v));
    }

    inline int64_t __lsp_forced_inline      byte_swap(int64_t v)
    {
        return byte_swap(uint64_t(v));
    }

    inline void __lsp_forced_inline         byte_swap(uint8_t *v, size_t n)
    {
    }

    inline void __lsp_forced_inline         byte_swap(int8_t *v, size_t n)
    {
    }

    inline void __lsp_forced_inline         byte_swap(wchar_t *v, size_t n)
    {
    #if defined(WCHART_16BIT)
        byte_swap(reinterpret_cast<uint16_t *>(v), n);
    #elif defined(WCHART_32BIT)
        byte_swap(reinterpret_cast<uint32_t *>(v), n);
    #else
        byte_swap(reinterpret_cast<unsigned int *>(v), n);
    #endif
    }

    template <class T>
    inline void byte_swap_copy(T *dst, const T *src, size_t n)
    {
        for (size_t i=0; i<n; ++i)
            dst[i]      = byte_swap(src[i]);
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ENDIAN_H_ */
