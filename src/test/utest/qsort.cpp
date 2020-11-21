/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 21 нояб. 2020 г.
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

#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/stdlib/stdlib.h>

#define ITEMS       0x10

UTEST_BEGIN("common", qsort)

    static int compare(const void *a, const void *b, void *arg)
    {
        bool *order = static_cast<bool *>(arg);
        const int *ia = static_cast<const int *>(a);
        const int *ib = static_cast<const int *>(b);

        return (*order) ? *ia - *ib : *ib - *ia;
    }

    UTEST_MAIN
    {
        int data[ITEMS];
        for (size_t i=0; i<ITEMS; ++i)
            data[i] = i;

        printf("Testing descending qsort_r...\n");
        bool asc = false;
        lsp::qsort_r(data, ITEMS, sizeof(int), compare, &asc);

        for (int i=0; i<ITEMS; ++i)
        {
            int ri = ITEMS - i - 1;
            if (data[ri] != i)
            {
                eprintf("data[%d] = %d, expected to be %d", ri, data[ri], i);
                UTEST_FAIL();
            }
        }

        printf("Testing ascending qsort_r...\n");
        asc = true;
        lsp::qsort_r(data, ITEMS, sizeof(int), compare, &asc);

        for (int i=0; i<ITEMS; ++i)
        {
            if (data[i] != i)
            {
                eprintf("data[%d] = %d, expected to be %d", i, data[i], i);
                UTEST_FAIL();
            }
        }
    }
UTEST_END;


