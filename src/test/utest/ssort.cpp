/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 24 мая 2026 г.
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

#include <lsp-plug.in/common/singletone.h>
#include <lsp-plug.in/stdlib/stdlib.h>
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/test-fw/FloatBuffer.h>

const float test1[] =
{
    10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f
};

const float test2[] =
{
    1.0f, 3.0f, 5.0f, 7.0f, 9.0f, 11.0f, 13.0f, 15.0f,
    2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f
};

const float test3[] =
{
    1.0f, 2.0f, 5.0f, 6.0f, 9.0f, 10.0f, 13.0f, 14.0f,
    3.0f, 4.0f, 7.0f, 8.0f, 11.0f, 12.0f, 15.0f, 16.0f
};

const float test4[] =
{
    0.0f, 8.0f, 4.0f, 12.0f, 2.0f, 10.0f, 6.0f, 14.0f,
    1.0f, 9.0f, 5.0f, 13.0f, 3.0f, 11.0f, 7.0f, 15.0f
};

const float test5[] =
{
    17.0f,
    0.0f, 8.0f, 4.0f, 12.0f, 2.0f, 10.0f, 6.0f, 14.0f,
    1.0f, 9.0f, 5.0f, 13.0f, 3.0f, 11.0f, 7.0f, 15.0f
};

UTEST_BEGIN("common", ssort)

    static int cmp_func(const void *a, const void *b)
    {
        const float *fa = static_cast<const float *>(a);
        const float *fb = static_cast<const float *>(b);
        return (*fa < *fb) ? -1 : (*fa > *fb) ? 1 : 0;
    }

    static int cmp_func_r(const void *a, const void *b, void *arg)
    {
        const float *fa = static_cast<const float *>(a);
        const float *fb = static_cast<const float *>(b);
        return (*fa < *fb) ? -1 : (*fa > *fb) ? 1 : 0;
    }

    void test_ssort(const char *name, const float *array, size_t length)
    {
        printf("Testing ssort '%s'...\n", name);
        FloatBuffer src(length);
        memcpy(src.data(), array, length * sizeof(float));
        FloatBuffer res(src);
        ssort(res.data(), length, sizeof(float), cmp_func);

        UTEST_ASSERT(!src.corrupted());
        UTEST_ASSERT(!res.corrupted());

        for (size_t i=1; i<length; ++i)
        {
            if (res[i] < res[i-1])
            {
                src.dump("src");
                res.dump("res");
                UTEST_FAIL_MSG("Invalid sort order");
            }
        }
    }

    void test_ssort_r(const char *name, const float *array, size_t length)
    {
        printf("Testing ssort_r '%s'...\n", name);
        FloatBuffer src(length);
        memcpy(src.data(), array, length * sizeof(float));
        FloatBuffer res(src);
        ssort_r(res.data(), length, sizeof(float), cmp_func_r, NULL);

        UTEST_ASSERT(!src.corrupted());
        UTEST_ASSERT(!res.corrupted());

        for (size_t i=1; i<length; ++i)
        {
            if (res[i] < res[i-1])
            {
                src.dump("src");
                res.dump("res");
                UTEST_FAIL_MSG("Invalid sort order");
            }
        }
    }

    void test_large_ssort()
    {
        UTEST_FOREACH(count,
            0xff0, 0xfff, 0x1000, 0x10000)
        {
            printf("Testing large ssort_r for %d elements...\n", int(count));
            FloatBuffer src(count);
            src.randomize_sign();
            FloatBuffer res(src);
            ssort(res.data(), src.size(), sizeof(float), cmp_func);

            UTEST_ASSERT(!src.corrupted());
            UTEST_ASSERT(!res.corrupted());

            for (size_t i=1; i<src.size(); ++i)
            {
                if (res[i] < res[i-1])
                {
                    src.dump("src");
                    res.dump("res");
                    UTEST_FAIL_MSG("Invalid sort order");
                }
            }
        }
    }

    void test_large_ssort_r()
    {
        UTEST_FOREACH(count,
            0xff0, 0xfff, 0x1000, 0x10000)
        {
            printf("Testing large ssort_r for %d elements...\n", int(count));
            FloatBuffer src(count);
            src.randomize_sign();
            FloatBuffer res(src);
            ssort_r(res.data(), src.size(), sizeof(float), cmp_func_r, NULL);

            UTEST_ASSERT(!src.corrupted());
            UTEST_ASSERT(!res.corrupted());

            for (size_t i=1; i<src.size(); ++i)
            {
                if (res[i] < res[i-1])
                {
                    src.dump("src");
                    res.dump("res");
                    UTEST_FAIL_MSG("Invalid sort order");
                }
            }
        }
    }

    UTEST_MAIN
    {
    #define CALL(array) \
        test_ssort(#array, array, sizeof(array)/sizeof(array[0])); \
        test_ssort_r(#array, array, sizeof(array)/sizeof(array[0]));

        CALL(test1);
        CALL(test2);
        CALL(test3);
        CALL(test4);
        CALL(test5);

        test_large_ssort();
        test_large_ssort_r();
    }
UTEST_END;


