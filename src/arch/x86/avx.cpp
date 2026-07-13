/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 13 июл. 2026 г.
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

#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/cpuid.h>
#include <lsp-plug.in/stdlib/string.h>

#ifdef ARCH_X86
    // Test framework
    #ifdef LSP_TESTING
        #include <lsp-plug.in/test-fw/test.h>
    #else
        #define TEST_EXPORT(...)
    #endif /* LSP_TESTING */

    #define PRIVATE_COMMON_ARCH_X86_AVX_IMPL
        #include <private/common/arch/x86/avx/memswap.h>
    #undef PRIVATE_COMMON_ARCH_X86_AVX_IMPL

    namespace lsp
    {
        namespace avx
        {
            #define EXPORT2(function, export) \
            { \
                lsp::function                       = avx::export; \
                TEST_EXPORT(avx::export); \
            }
            #define EXPORT1(function)                   EXPORT2(function, function);

            LSP_HIDDEN_MODIFIER
            void init_common_lib(const cpuid_t & f)
            {
                if (!(f.hwcap[0] & CPU_HWCAP0_AVX))
                    return;

                EXPORT1(memswap);
            }

            #undef EXPORT1
            #undef EXPORT2
        } /* namespace avx */
    } /* namespace lsp */

#endif /* ARCH_X86 */




