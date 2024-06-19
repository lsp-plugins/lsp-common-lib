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

    void test_cas()
    {
        size_t i;
        atomic_t value;
        atomic_store(&value, 0);

        printf("Testing atomic_cas...\n");

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, 0, 1))
                break;
        UTEST_ASSERT(i < 1000);

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, 0, 1))
                break;
        UTEST_ASSERT(i >= 1000);

        for (i=0; i<1000; ++i)
            if (atomic_cas(&value, 1, 2))
                break;
        UTEST_ASSERT(i < 1000);
        UTEST_ASSERT(atomic_load(&value) == 2);
    }

    void test_swap()
    {
        atomic_t value1, value2;
        atomic_store(&value1, 0);
        atomic_store(&value2, 1);
        printf("Testing atomic_swap...\n");

        atomic_swap(&value1, 2);
        atomic_swap(&value2, 3);

        UTEST_ASSERT(atomic_load(&value1) == 2);
        UTEST_ASSERT(atomic_load(&value2) == 3);

        atomic_swap(&value1, value2);

        UTEST_ASSERT(atomic_load(&value1) == 3);
    }

    void test_add()
    {
        atomic_t value;
        atomic_store(&value, 0);
        printf("Testing atomic_add...\n");

        for (size_t i=0; i<1000; ++i)
            UTEST_ASSERT(atomic_add(&value, 1) == atomic_t(i)); // i == previous value
        UTEST_ASSERT(atomic_load(&value) == 1000);
    }

    UTEST_MAIN
    {
        test_cas();
        test_swap();
        test_add();
    }
UTEST_END;


