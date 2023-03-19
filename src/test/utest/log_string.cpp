/*
 * Copyright (C) 2023 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2023 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 25 февр. 2023 г.
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

#include <lsp-plug.in/common/debug.h>
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/test-fw/utest.h>

using namespace lsp;

UTEST_BEGIN("common", log_string)

    void test_ascii()
    {
        static const char src[] = {
            't', 'e', 's', 't', ' ',
            char(0x9a), char(0x9b), char(0x9c),
            '\0'
        };

        printf("Testing ASCII log_string conversion...\n");
        debug::log_string res = src;
        UTEST_ASSERT(res.c_str() != NULL);
        UTEST_ASSERT_MSG(
            strcmp(res.c_str(), src) == 0,
            "Failed string conversion '%s': got '%s', expected '%s'",
            src, res.c_str(), src
        );
    }

    void test_utf16()
    {
        static const lsp_utf16_t src[] =
        {
            't', 'e', 's', 't', ' ',
            0x9a, 0x9b, 0x9c,
            0x123, 0x1234, 0x4321,
            '\0'
        };

        static const char *expected="test \\x9a\\x9b\\x9c\\u0123\\u1234\\u4321";

        printf("Testing UTF-16 log_string conversion...\n");
        debug::log_string res = src;
        UTEST_ASSERT(res.c_str() != NULL);
        UTEST_ASSERT_MSG(
            strcmp(res.c_str(), expected) == 0,
            "Failed string conversion: got '%s', expected '%s'",
            res.c_str(), expected
        );
    }

    void test_utf32()
    {
        static const lsp_utf32_t src[] =
        {
            't', 'e', 's', 't', ' ',
            0x9a, 0x9b, 0x9c,
            0x123, 0x1234, 0x12345, 0x123456, 0x1234567, 0x12345678,
            '\0'
        };

        static const char *expected="test \\x9a\\x9b\\x9c\\U123\\U1234\\U12345\\U123456\\U1234567\\U12345678";

        printf("Testing UTF-32 log_string conversion...\n");
        debug::log_string res = src;
        UTEST_ASSERT(res.c_str() != NULL);
        UTEST_ASSERT_MSG(
            strcmp(res.c_str(), expected) == 0,
            "Failed string conversion: got '%s', expected '%s'",
            res.c_str(), expected
        );
    }

    UTEST_MAIN
    {
        test_ascii();
        test_utf16();
        test_utf32();
    }
UTEST_END;



