/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 4 апр. 2020 г.
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

#include <lsp-plug.in/stdlib/stdio.h>

#include <stdlib.h>
#include <unistd.h>

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif /* PLATFORM_WINDOWS */

namespace lsp
{
#ifdef PLATFORM_WINDOWS
    LSP_COMMON_LIB_EXPORT
    int vasprintf(char **res, const char *fmt, va_list ap)
    {
        int len = vsnprintf(NULL, 0, fmt, ap);
        if (len < 0)
            return -1;

        char *str = reinterpret_cast<char *>(malloc(size_t(len) + 1));
        if (str == NULL)
            return -1;

        int r = vsnprintf(str, len + 1, fmt, ap);
        if (r < 0)
        {
            free(str);
            return -1;
        }

        *res = str;
        return r;
    }

    LSP_COMMON_LIB_EXPORT
    int asprintf(char **strp, const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);

        int r = vasprintf(strp, fmt, ap);

        va_end(ap);
        return r;
    }

    LSP_COMMON_LIB_EXPORT
    int fdsync(FILE *fd)
    {
        return (FlushFileBuffers((HANDLE)_fileno(fd))) ? 0 : -1;
    }

#endif /* PLATFORM_WINDOWS */

#ifdef PLATFORM_UNIX_COMPATIBLE

    LSP_COMMON_LIB_EXPORT
    int fdsync(FILE *fd)
    {
        return ::fsync(fileno(fd));
    }
#endif /* PLATFORM_UNIX_COMPATIBLE */

}



