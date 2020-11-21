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

#ifndef LSP_PLUG_IN_STDLIB_STDLIB_H_
#define LSP_PLUG_IN_STDLIB_STDLIB_H_

#include <lsp-plug.in/common/version.h>
#include <stdlib.h>

namespace lsp
{
    typedef int (*sort_compar_t)(const void *a, const void *ab, void *arg);

    #if defined(PLATFORM_BSD) || defined(PLATFORM_MACOSX)
        typedef struct bsd_qsort_r_t
        {
            void             *arg;
            sort_compar_t     compar;

            static int        compare(void *s, const void *a, const void *b);
        } bsd_qsort_r_t;
    #endif /* defined(PLATFORM_BSD) || defined(PLATFORM_MACOSX) */

    #if defined(PLATFORM_WINDOWS)
        typedef struct win_qsort_r_t
        {
            void             *arg;
            sort_compar_t     compar;

            static int        compare(void *s, const void *a, const void *b);
        } win_qsort_r_t;
    #endif /* defined(PLATFORM_WINDOWS) */

    inline void qsort_r(
            void *data, size_t count, size_t szof,
            int (*compar)(const void *a1, const void *a2, void *data),
            void *arg
    )
    {
        #if defined(PLATFORM_LINUX) || defined(_GNU_SOURCE) || defined(__GNU__) || defined(COMPILER_GCC)
            ::qsort_r(data, count, szof, compar, arg);
        #elif defined(PLATFORM_BSD) || defined(PLATFORM_MACOSX)

            bsd_qsort_r_t sort;
            sort.arg        = arg;
            sort.compar     = compar;
            ::qsort_r(data, count, szof, &sort, &bsd_qsort_r_t::compare);

        #elif defined(PLATFORM_WINDOWS)

            win_qsort_r_t sort;
            sort.arg        = arg;
            sort.compar     = compar;

            ::qsort_s(data, count, szof, &win_qsort_r_t::compare, &tmp);

        #else
            ::qsort_r(data, count, szof, compar, arg);
        #endif
    }
}

#endif /* LSP_PLUG_IN_STDLIB_STDLIB_H_ */
