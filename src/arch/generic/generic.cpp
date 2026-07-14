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

#include <lsp-plug.in/common/cpuid.h>
#include <lsp-plug.in/common/static.h>
#include <lsp-plug.in/stdlib/string.h>

#define PRIVATE_COMMON_ARCH_GENERIC_IMPL
    #include <private/common/arch/generic/memswap.h>
#undef PRIVATE_COMMON_ARCH_GENERIC_IMPL

// Test framework
#ifdef LSP_TESTING
    #include <lsp-plug.in/test-fw/test.h>
#else
    #define TEST_EXPORT(...)
#endif /* LSP_TESTING */

namespace lsp
{
    LSP_COMMON_LIB_PUBLIC
    memswap_t memswap   = generic::memswap;

#if defined(ARCH_X86)
    namespace x86
    {
        LSP_HIDDEN_MODIFIER
        void init_common_lib(const cpuid_t & f);
    } /* namespace x86 */
#endif

#if defined(ARCH_ARM)
    namespace arm
    {
        LSP_HIDDEN_MODIFIER
        void init_common_lib(const cpuid_t & f);
    } /* namespace arm */
#endif

    LSP_HIDDEN_MODIFIER
    void init_common_lib()
    {
        cpuid_t info;
        cpuid(&info);

        TEST_EXPORT(generic::memswap);

        IF_ARCH_X86(x86::init_common_lib(info));
        IF_ARCH_ARM(arm::init_common_lib(info));
    }

    static StaticInitializer common_lib_initializer(init_common_lib);

} /* namespace lsp */


