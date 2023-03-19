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

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif /* PLATFORM_WINDOWS */

namespace lsp
{
#ifdef PLATFORM_WINDOWS
    LSP_COMMON_LIB_PUBLIC
    int vasprintf(char **res, const char *fmt, va_list ap)
    {
        int len = _vscprintf(fmt, ap);
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

    LSP_COMMON_LIB_PUBLIC
    int asprintf(char **strp, const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);

        int r = vasprintf(strp, fmt, ap);

        va_end(ap);
        return r;
    }

    LSP_COMMON_LIB_PUBLIC
    int fdsync(FILE *fd)
    {
        /*
         * When stdin, stdout, and stderr aren't associated with a stream (for example, in
         * a Windows application without a console window), the file descriptor values for
         * these streams are returned from _fileno as the special value -2. Similarly, if you
         * use a 0, 1, or 2 as the file descriptor parameter instead of the result of a call to
         * _fileno, _get_osfhandle also returns the special value -2 when the file descriptor
         * is not associated with a stream, and does not set errno. However, this is not a valid
         * file handle value, and subsequent calls that attempt to use it are likely to fail.
         */
        int fd_id = _fileno(fd);
        if (fd_id == -2)
            return -1;

        intptr_t hfd = _get_osfhandle(fd_id);
        if (hfd == -2)
            return -1;

        return (FlushFileBuffers(reinterpret_cast<HANDLE>(hfd))) ? 0 : -1;
    }

#endif /* PLATFORM_WINDOWS */

#ifdef PLATFORM_UNIX_COMPATIBLE

    LSP_COMMON_LIB_PUBLIC
    int fdsync(FILE *fd)
    {
        return ::fsync(fileno(fd));
    }
#endif /* PLATFORM_UNIX_COMPATIBLE */

}



