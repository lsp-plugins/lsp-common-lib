/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 2 апр. 2020 г.
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

#ifndef LSP_PLUG_IN_STDLIB_STRING_H_
#define LSP_PLUG_IN_STDLIB_STRING_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

#include <string.h>
#include <strings.h>
#include <stdlib.h>

#if defined(PLATFORM_WINDOWS)
    inline char *stpcpy(char *dst, const char *src)
    {
        size_t len = ::strlen(src);
        ::memcpy(dst, src, len + 1);
        return &dst[len];
    }

    inline void bzero(void *dst, size_t count)
    {
        ::memset(dst, 0, count);
    }

    inline char *strndup(const char *src, size_t clen)
    {
        size_t nlen = ::strnlen(src, clen);
        char *ptr   = reinterpret_cast<char *>(::malloc(nlen + 1));
        if (ptr != NULL)
        {
            ::memcpy(ptr, src, nlen);
            ptr[nlen]   = '\0';
        }

        return ptr;
    }
#endif /* PLATFORM_WINDOWS */

namespace lsp
{
    inline void *memdup(const void *src, size_t count)
    {
        void *dst = ::malloc(count);
        if ((dst != NULL) && (count > 0))
            ::memcpy(dst, src, count);
        return dst;
    }
}

#endif /* LSP_PLUG_IN_STDLIB_STRING_H_ */
