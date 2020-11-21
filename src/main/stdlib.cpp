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

#include <lsp-plug.in/stdlib/stdlib.h>

namespace lsp
{
    #if defined(PLATFORM_BSD) || defined(PLATFORM_MACOSX)
        int bsd_qsort_r_t::compare(void *s, const void *a, const void *b)
        {
            bsd_qsort_r_t *_this = static_cast<bsd_qsort_r_t *>(s);
            return (_this->compar)(a, b, ss->arg);
        }
    #endif /* defined(PLATFORM_BSD) || defined(PLATFORM_MACOSX) */

    #if defined(PLATFORM_WINDOWS)
        int win_qsort_r_t::compare(void *s, const void *a, const void *b)
        {
            win_qsort_r_t *_this = static_cast<win_qsort_r_t *>(s);
            return (_this->compar)(a, b, ss->arg);
        }
    #endif /* defined(PLATFORM_WINDOWS) */
}


