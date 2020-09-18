/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 7 апр. 2020 г.
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

#include <lsp-plug.in/common/debug.h>
#include <lsp-plug.in/stdlib/stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace lsp
{
    namespace debug
    {
        static FILE *log_fd = stderr;

        LSP_COMMON_LIB_EXPORT
        void redirect(const char *file)
        {
            if (log_fd != stderr)
                return;

            #if defined(PLATFORM_WINDOWS)
                char *tmpdir = getenv("TEMP");
                if (tmpdir == NULL)
                    tmpdir = getenv("TMP");
                if (tmpdir == NULL)
                    return;

                return redirect(tmpdir, file);
            #else
                return redirect("/tmp", file);
            #endif
        }

        LSP_COMMON_LIB_EXPORT
        void redirect(const char *path, const char *file)
        {
            if (log_fd != stderr)
                return;

            char *tmppath = NULL;
            int n = asprintf(&tmppath, "%s" FILE_SEPARATOR_S "%s", path, file);
            if ((n < 0) || (tmppath == NULL))
                return;

            FILE *fd = NULL;

        #ifndef PLATFORM_WINDOWS
            ::fprintf(stderr, "Log data will be written to file: %s\n", path);
            ::fflush(stderr);

            fd  = ::fopen(tmppath, "a");
            if (fd != NULL)
            {
                ::setvbuf(fd, NULL, _IONBF, BUFSIZ);
                ::fclose(stderr);
                ::dup2(fileno(fd), STDERR_FILENO);
            }
        #endif

            if (!fd)
            {
                ::fprintf(stderr, "Failed to open file %s, continuing redirect to STDERR\n", path);
                ::fflush(stderr);
            }
            ::free(tmppath);
        }

        LSP_COMMON_LIB_EXPORT
        int vprintf(const char *fmt, va_list args)
        {
            if (log_fd == NULL)
                return 0;

            int res = ::vfprintf(log_fd, fmt, args);
            ::fflush(log_fd);
            return res;
        }

        LSP_COMMON_LIB_EXPORT
        int printf(const char *fmt...)
        {
            va_list ap;
            va_start(ap, fmt);

            int r = vprintf(fmt, ap);

            va_end(ap);
            return r;
        }

        LSP_COMMON_LIB_EXPORT
        void dumpf(const char *s, const char *fmt, const float *f, size_t n)
        {
            ::fputs(s, log_fd);
            ::fputs(": ", log_fd);
            while (n--)
            {
                ::fprintf(log_fd, fmt, *(f++));
                if (n > 0)
                    ::fputc(' ', log_fd);
            }
            ::fputs("\n", log_fd);
            ::fflush(log_fd);
        }

        LSP_COMMON_LIB_EXPORT
        void dumpb(const char *s, const void *b, size_t sz)
        {
            ::fputs(s, log_fd);
            ::fputs(":\n", log_fd);

            const uint8_t *ddump        = reinterpret_cast<const uint8_t *>(b);

            for (size_t offset=0; offset < sz; offset += 16)
            {
                // Print HEX dump
                ::fprintf(log_fd, "%08x: ", int(offset));
                for (size_t i=0; i<0x10; ++i)
                {
                    if ((offset + i) < sz)
                        ::fprintf(log_fd, "%02x ", int(ddump[i]));
                    else
                        ::fprintf(log_fd, "   ");
                }
                ::fprintf(log_fd, "   ");

                // Print character dump
                for (size_t i=0; i<0x10; ++i)
                {
                    if ((offset + i) < sz)
                    {
                        uint8_t c   = ddump[i];
                        if ((c < 0x20) || (c >= 0x80))
                            c           = '.';
                        ::fprintf(log_fd, "%c", c);
                    }
                    else
                        ::fputc(' ', log_fd);
                }
                ::fputs("\n", log_fd);

                // Move pointer
                ddump       += 0x10;
            }

            ::fflush(log_fd);
        }
    }
}


