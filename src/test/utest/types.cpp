/*
 * Copyright (C) 2025 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2025 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 3 мар. 2025 г.
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

using namespace lsp;

UTEST_BEGIN("common", types)

    template <class type>
    void test_cast(type value)
    {
        auto casted = lsp::fixed_int(value);
        UTEST_ASSERT(sizeof(casted) == sizeof(value));
    }

    UTEST_MAIN
    {
        char str[8];
        const char *cstr = "test";

        test_cast<char>(static_cast<char>(42));
        test_cast<short>(static_cast<short>(42));
        test_cast<int>(static_cast<int>(42));
        test_cast<long>(static_cast<long>(42));
        test_cast<long long>(static_cast<long long>(42));

        test_cast<signed char>(static_cast<signed char>(42));
        test_cast<signed short>(static_cast<signed short>(42));
        test_cast<signed int>(static_cast<signed int>(42));
        test_cast<signed long>(static_cast<signed long>(42));
        test_cast<signed long long>(static_cast<signed long long>(42));

        test_cast<unsigned char>(static_cast<unsigned char>(42));
        test_cast<unsigned short>(static_cast<unsigned short>(42));
        test_cast<unsigned int>(static_cast<unsigned int>(42));
        test_cast<unsigned long>(static_cast<unsigned long>(42));
        test_cast<unsigned long long>(static_cast<unsigned long long>(42));

        test_cast<char *>(reinterpret_cast<char *>(str));
        test_cast<short *>(reinterpret_cast<short *>(str));
        test_cast<int *>(reinterpret_cast<int *>(str));
        test_cast<long *>(reinterpret_cast<long *>(str));
        test_cast<long long *>(reinterpret_cast<long long *>(str));

        test_cast<signed char *>(reinterpret_cast<signed char *>(str));
        test_cast<signed short *>(reinterpret_cast<signed short *>(str));
        test_cast<signed int *>(reinterpret_cast<signed int *>(str));
        test_cast<signed long *>(reinterpret_cast<signed long *>(str));
        test_cast<signed long long *>(reinterpret_cast<signed long long *>(str));

        test_cast<unsigned char *>(reinterpret_cast<unsigned char *>(str));
        test_cast<unsigned short *>(reinterpret_cast<unsigned short *>(str));
        test_cast<unsigned int *>(reinterpret_cast<unsigned int *>(str));
        test_cast<unsigned long *>(reinterpret_cast<unsigned long *>(str));
        test_cast<unsigned long long *>(reinterpret_cast<unsigned long long *>(str));

        test_cast<const char *>(reinterpret_cast<const char *>(cstr));
        test_cast<const short *>(reinterpret_cast<const short *>(cstr));
        test_cast<const int *>(reinterpret_cast<const int *>(cstr));
        test_cast<const long *>(reinterpret_cast<const long *>(cstr));
        test_cast<const long long *>(reinterpret_cast<const long long *>(cstr));

        test_cast<const signed char *>(reinterpret_cast<const signed char *>(cstr));
        test_cast<const signed short *>(reinterpret_cast<const signed short *>(cstr));
        test_cast<const signed int *>(reinterpret_cast<const signed int *>(cstr));
        test_cast<const signed long *>(reinterpret_cast<const signed long *>(cstr));
        test_cast<const signed long long *>(reinterpret_cast<const signed long long *>(cstr));

        test_cast<const unsigned char *>(reinterpret_cast<const unsigned char *>(cstr));
        test_cast<const unsigned short *>(reinterpret_cast<const unsigned short *>(cstr));
        test_cast<const unsigned int *>(reinterpret_cast<const unsigned int *>(cstr));
        test_cast<const unsigned long *>(reinterpret_cast<const unsigned long *>(cstr));
        test_cast<const unsigned long long *>(reinterpret_cast<const unsigned long long *>(cstr));
    }

UTEST_END;



