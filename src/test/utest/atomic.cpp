/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 31 мар. 2020 г.
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

#include <lsp-plug.in/common/atomic.h>
#include <lsp-plug.in/test-fw/utest.h>

using namespace lsp;

UTEST_BEGIN("common", atomic)

    template <class T>
    void test_cas(const char *type)
    {
        size_t i;
        T value;
        atomic_store(&value, T(0));

        printf("Testing atomic_cas for %s...\n", type);

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, T(0), T(1)))
                break;
        UTEST_ASSERT(i < 1000);

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, T(0), T(1)))
                break;
        UTEST_ASSERT(i >= 1000);

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, T(1), T(2)))
                break;
        UTEST_ASSERT(i < 1000);
        UTEST_ASSERT(atomic_load(&value) == T(2));
    }

    template <class T>
    void test_swap(const char *type)
    {
        T value1, value2;
        atomic_store(&value1, T(0));
        atomic_store(&value2, T(1));

        printf("Testing atomic_swap for %s...\n", type);

        atomic_swap(&value1, T(2));
        atomic_swap(&value2, T(3));

        UTEST_ASSERT(atomic_load(&value1) == T(2));
        UTEST_ASSERT(atomic_load(&value2) == T(3));

        atomic_swap(&value1, value2);

        UTEST_ASSERT(atomic_load(&value1) == T(3));
    }

    template <class T>
    void test_add(const char *type)
    {
        T value;
        atomic_store(&value, T(0));
        printf("Testing atomic_add for %s...\n", type);

        for (size_t i=0; i<0x40; ++i)
            UTEST_ASSERT(atomic_add(&value, T(1)) == T(i)); // i == previous value
        UTEST_ASSERT(atomic_load(&value) == T(0x40));
    }

    UTEST_MAIN
    {
        test_cas<int8_t>("int8_t");
        test_cas<uint8_t>("uint8_t");
        test_cas<int16_t>("int16_t");
        test_cas<uint16_t>("uint16_t");
        test_cas<int32_t>("int32_t");
        test_cas<uint32_t>("uint32_t");
    #if defined(ARCH_64BIT)
        test_cas<int64_t>("int64_t");
        test_cas<uint64_t>("uint64_t");
    #endif /* ARCH_64BIT */
        test_cas<size_t>("size_t");
        test_cas<ssize_t>("ssize_t");

        test_swap<int8_t>("int8_t");
        test_swap<uint8_t>("uint8_t");
        test_swap<int16_t>("int16_t");
        test_swap<uint16_t>("uint16_t");
        test_swap<int32_t>("int32_t");
        test_swap<uint32_t>("uint32_t");
    #if defined(ARCH_64BIT)
        test_swap<int32_t>("int64_t");
        test_swap<uint32_t>("uint64_t");
    #endif /* ARCH_64BIT */
        test_swap<size_t>("size_t");
        test_swap<ssize_t>("ssize_t");

        test_add<int8_t>("int8_t");
        test_add<uint8_t>("uint8_t");
        test_add<int16_t>("int16_t");
        test_add<uint16_t>("uint16_t");
        test_add<int32_t>("int32_t");
        test_add<uint32_t>("uint32_t");
    #if defined(ARCH_64BIT)
        test_add<int64_t>("int64_t");
        test_add<uint64_t>("uint64_t");
    #endif /* ARCH_64BIT */
        test_add<size_t>("size_t");
        test_add<ssize_t>("ssize_t");
    }
UTEST_END;


