/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
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
    /**
     * Memory swap function
     * @param a pointer to first non-interleaving chunk of memory
     * @param b pointer to second non-interleaving chunk of memory
     * @param count number of bytes to swap
     */
    typedef void (* memswap_t)(void *a, void *b, size_t count);

    inline void *memdup(const void *src, size_t count)
    {
        void *dst = ::malloc(count);
        if ((dst != NULL) && (count > 0))
            ::memcpy(dst, src, count);
        return dst;
    }

    inline char *strend(char *str)
    {
        return &str[strlen(str)];
    }

    inline const char *strend(const char *str)
    {
        return &str[strlen(str)];
    }

    inline char *strmemdup(const void *src, size_t count)
    {
        char *dst = static_cast<char *>(::malloc(count + 1));
        if (dst != NULL)
        {
            ::memcpy(dst, src, count);
            dst[count] = '\0';
        }
        return dst;
    }

#if defined(PLATFORM_MACOSX)
    inline void *mempcpy(void *dest, const void *src, size_t n)
    {
        return static_cast<uint8_t *>(memcpy(dest, src, n)) + n;
    }
#endif /* PLATFORM_MACOSX */

    /**
     * Rotate memory buffer left by specified number of bytes.
     * Example:
     *   buffer:          0 1 2 3 4 5 6 7
     *   memrotate by 3:  3 4 5 6 7 0 1 2
     *
     * @param ptr pointer to memory buffer
     * @param length the overall buffer length
     * @param count number of bytes to perform rotation
     */
    void memrotate(void *ptr, size_t length, size_t count);

    extern "C" {
        LSP_COMMON_LIB_PUBLIC
        extern memswap_t memswap;
    } /* extern "C" */
} /* namespace lsp */

#endif /* LSP_PLUG_IN_STDLIB_STRING_H_ */
