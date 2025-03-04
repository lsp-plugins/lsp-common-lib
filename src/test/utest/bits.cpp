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

#include <lsp-plug.in/common/bits.h>
#include <lsp-plug.in/test-fw/utest.h>

using namespace lsp;

UTEST_BEGIN("common", bits)
    template <typename T>
    void test_reverse_bits(const char *label)
    {
        printf("Testing reverse_bits for %s...\n", label);
        const size_t n = sizeof(T) * 8;

        for (size_t i=0; i<n; ++i)
        {
            T x     = T(1) << i;
            T y     = reverse_bits(x);
            T ck    = (T(1) << (n - i - 1));
            UTEST_ASSERT_MSG(y == ck, "%s: tier1, i=%d, n=%d, x=0x%08llx, y=0x%08llx, ck=0x%08llx",
                label, int(i), int(n),
                (long long)x,
                (long long)y,
                (long long)ck);
        }

        for (size_t i=0; i<(n - 4); ++i)
        {
            T x     = T(1) << i;
            T y     = reverse_bits(x, n - 4);
            T ck    = (T(1) << (n - 5 - i));
            UTEST_ASSERT_MSG(y == ck, "%s: tier2, i=%d, n=%d, x=0x%08llx, y=0x%08llx, ck=0x%08llx",
                label, int(i), int(n),
                (long long)x,
                (long long)y,
                (long long)ck);
        }

        for (size_t i=0; i<4; ++i)
        {
            T x     = T(1) << i;
            T y     = reverse_bits(x, 4);
            T ck    = (T(1) << (3 - i));
            UTEST_ASSERT_MSG(y == ck, "%s: tier3, i=%d, n=%d, x=0x%08llx, y=0x%08llx, ck=0x%08llx",
                label, int(i), int(n),
                (long long)x,
                (long long)y,
                (long long)ck);
        }
    }

    template <typename T>
    void test_int_log2(const char *label)
    {
        printf("Testing int_log2 for %s...\n", label);

        int log2 = int_log2(T(0));
        UTEST_ASSERT_MSG(log2 == 0, "%s: zero input detected as %d", label, log2);

        for (int i=0; i<int(sizeof(T)*8); ++i)
        {
            T x     = T(1) << i;
            int y   = int_log2(x);
            UTEST_ASSERT_MSG(y == i, "%s: bit=%d but detected as %d", label, i, y);
        }
    }

    void test_pow2_rounding()
    {
        uint32_t x = 0x100;

        printf("Testing round_pow2...\n");

        UTEST_ASSERT(round_pow2(x) == x);
        for (uint32_t i = 1; i<=x; ++i)
            UTEST_ASSERT(round_pow2(x + i) == (x << 1));
    }

    UTEST_MAIN
    {
        test_reverse_bits<uint8_t>("uint8_t");
        test_reverse_bits<int8_t>("int8_t");
        test_reverse_bits<uint16_t>("uint16_t");
        test_reverse_bits<int16_t>("int16_t");
        test_reverse_bits<uint32_t>("uint32_t");
        test_reverse_bits<int32_t>("int32_t");
        test_reverse_bits<uint64_t>("uint64_t");
        test_reverse_bits<int64_t>("int64_t");
        test_reverse_bits<size_t>("size_t");
        test_reverse_bits<ssize_t>("ssize_t");

        test_int_log2<uint8_t>("uint8_t");
        test_int_log2<int8_t>("int8_t");
        test_int_log2<uint16_t>("uint16_t");
        test_int_log2<int16_t>("int16_t");
        test_int_log2<uint32_t>("uint32_t");
        test_int_log2<int32_t>("int32_t");
        test_int_log2<uint64_t>("uint64_t");
        test_int_log2<int64_t>("int64_t");
        test_int_log2<size_t>("size_t");
        test_int_log2<ssize_t>("ssize_t");

        test_pow2_rounding();
    }

UTEST_END;


