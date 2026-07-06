/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 5 июл. 2026 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_X86_HWCAP_H_
#define LSP_PLUG_IN_COMMON_ARCH_X86_HWCAP_H_

#include <lsp-plug.in/common/types.h>

namespace lsp
{
    enum cpu_hwcap0_t
    {
        // Different legacy feature set
        CPU_HWCAP0_FPU              = 1 << 0,
        CPU_HWCAP0_CMOV             = 1 << 1,
        CPU_HWCAP0_MOVBE            = 1 << 2,
        CPU_HWCAP0_MMX              = 1 << 3,

        // SSE feature set
        CPU_HWCAP0_FXSAVE           = 1 << 4,
        CPU_HWCAP0_SSE              = 1 << 5,
        CPU_HWCAP0_SSE2             = 1 << 6,
        CPU_HWCAP0_SSE3             = 1 << 7,
        CPU_HWCAP0_SSSE3            = 1 << 8,
        CPU_HWCAP0_SSE4_1           = 1 << 9,
        CPU_HWCAP0_SSE4_2           = 1 << 10,
        CPU_HWCAP0_SSE4A            = 1 << 11,

        // AVX and FMA feature set
        CPU_HWCAP0_XSAVE            = 1 << 12,
        CPU_HWCAP0_FMA3             = 1 << 13,
        CPU_HWCAP0_FMA4             = 1 << 14,
        CPU_HWCAP0_AVX              = 1 << 15,
        CPU_HWCAP0_AVX2             = 1 << 16,

        // AVX-512 feature set
        CPU_HWCAP0_OSXSAVE          = 1 << 17,
        CPU_HWCAP0_AVX512F          = 1 << 18,
        CPU_HWCAP0_AVX512DQ         = 1 << 19,
        CPU_HWCAP0_AVX512IFMA       = 1 << 20,
        CPU_HWCAP0_AVX512PF         = 1 << 21,
        CPU_HWCAP0_AVX512ER         = 1 << 22,
        CPU_HWCAP0_AVX512CD         = 1 << 23,
        CPU_HWCAP0_AVX512BW         = 1 << 24,
        CPU_HWCAP0_AVX512VL         = 1 << 25,
        CPU_HWCAP0_AVX512VBMI       = 1 << 26,
    };

} /* namespace lsp */


#endif /* LSP_PLUG_IN_COMMON_ARCH_X86_HWCAP_H_ */
