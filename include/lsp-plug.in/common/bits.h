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

#ifndef LSP_PLUG_IN_COMMON_BITS_H_
#define LSP_PLUG_IN_COMMON_BITS_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

// Declare array only for specific architectures
#if defined(ARCH_ARM7) || defined(ARCH_ARM6)
    /* nothing */
#elif defined(ARCH_AARCH64)
    /* nothing */
#else
namespace lsp
{
    LSP_COMMON_LIB_PUBLIC
    extern const uint8_t    lsp_rb_data[];
} /* namespace lsp */
#endif

// Include CPU-optimized code for bit reversal
#define LSP_PLUG_IN_COMMON_BITS_IMPL
    #if defined(ARCH_X86)
        #include <lsp-plug.in/common/arch/x86/bits/reverse.h>
        #include <lsp-plug.in/common/arch/x86/bits/int_log2.h>
    #elif defined(ARCH_AARCH64)
        #include <lsp-plug.in/common/arch/aarch64/bits/reverse.h>
        #include <lsp-plug.in/common/arch/aarch64/bits/int_log2.h>
    #elif defined(ARCH_ARM7)
        #include <lsp-plug.in/common/arch/arm/bits/reverse-armv7.h>
        #include <lsp-plug.in/common/arch/arm/bits/int_log2.h>
    #elif defined(ARCH_ARM6)
        #include <lsp-plug.in/common/arch/arm/bits/reverse-armv6.h>
        #include <lsp-plug.in/common/arch/arm/bits/int_log2.h>
    #else
        #include <lsp-plug.in/common/arch/generic/bits/reverse.h>
        #include <lsp-plug.in/common/arch/generic/bits/int_log2.h>
    #endif
#undef LSP_PLUG_IN_COMMON_BITS_IMPL


#endif /* LSP_PLUG_IN_COMMON_BITS_H_ */
