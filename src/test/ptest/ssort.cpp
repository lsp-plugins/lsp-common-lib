/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 25 мая 2026 г.
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


#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/stdlib/stdlib.h>
#include <lsp-plug.in/test-fw/ptest.h>
#include <lsp-plug.in/test-fw/helpers.h>

#define MIN_RANK 8
#define MAX_RANK 16

//-----------------------------------------------------------------------------
// Performance test for complex division
PTEST_BEGIN("common", ssort, 5, 20)

    static int float_cmp(const void *a, const void *b, void *arg)
    {
        const float *fa = static_cast<const float *>(a);
        const float *fb = static_cast<const float *>(b);
        return (*fa < *fb) ? -1 : (*fa > *fb) ? 1 : 0;
    }

    void call(const char *label, float *dst, float *src, size_t count, sort_r_t sort)
    {
        char buf[80];
        snprintf(buf, sizeof(buf), "%s x %d", label, int(count));
        printf("Testing %s numbers...\n", buf);

        PTEST_LOOP(buf,
            randomize_sign(src, count);
            for (size_t i=0; i<50; ++i)
            {
                memcpy(dst, src, count * sizeof(float));
                sort(dst, count, sizeof(float), float_cmp, NULL);
            }
        );
    }

    PTEST_MAIN
    {
        size_t buf_size = 1 << MAX_RANK;
        uint8_t *data   = NULL;
        float *out      = alloc_aligned<float>(data, buf_size * 2, 64);
        float *in       = &out[buf_size];
        lsp_finally { free_aligned(data); };

        #define CALL(func) \
            call(#func, out, in, count, func)

        for (size_t i=MIN_RANK; i <= MAX_RANK; ++i)
        {
            size_t count = 1 << i;

            CALL(qsort_r);
            CALL(ssort_r);

            PTEST_SEPARATOR;
        }

        free_aligned(data);
    }
PTEST_END








