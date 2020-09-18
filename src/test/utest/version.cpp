/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 3 мая 2020 г.
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
#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/stdlib/string.h>

UTEST_BEGIN("common", version)

    UTEST_MAIN
    {
        static const lsp::version_t ver1 = LSP_DEF_VERSION(1, 2, 3);
        static const lsp::version_t ver2 = LSP_DEFINE_VERSION(LSP_COMMON_LIB);

        static const char *ver3 = LSP_DEF_VERSION_STR(1, 2, 3);
        static const char *ver4 = LSP_DEF_VERSION_STR(LSP_COMMON_LIB_MAJOR, LSP_COMMON_LIB_MINOR, LSP_COMMON_LIB_MICRO);
        static const char *ver5 = LSP_DEFINE_VERSION_STR(LSP_COMMON_LIB);

        static const lsp::version_t ver6 = LSP_DEF_VERSION(1, 3, 0);

        printf("Library version: %s\n", ver5);

        UTEST_ASSERT(ver1.major == 1);
        UTEST_ASSERT(ver1.minor == 2);
        UTEST_ASSERT(ver1.micro == 3);

        UTEST_ASSERT(ver2.major == LSP_COMMON_LIB_MAJOR);
        UTEST_ASSERT(ver2.minor == LSP_COMMON_LIB_MINOR);
        UTEST_ASSERT(ver2.micro == LSP_COMMON_LIB_MICRO);

        UTEST_ASSERT(::strcmp(ver3, "1.2.3") == 0);
        UTEST_ASSERT(::strcmp(ver4, ver5) == 0);

        UTEST_ASSERT(lsp::version_cmp(&ver1, &ver6) < 0);
        UTEST_ASSERT(lsp::version_cmp(ver6, ver1) > 0);
        UTEST_ASSERT(lsp::version_cmp(ver1, ver1) == 0);
    }

UTEST_END;


