/*
 * debug.cpp
 *
 *  Created on: 7 апр. 2020 г.
 *      Author: sadko
 */

#include <lsp-plug.in/common/debug.h>
#include <lsp-plug.in/stdlib/stdio.h>
#include <stdlib.h>

namespace lsp
{
    namespace debug
    {
        static FILE *log_fd = stderr;

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

            FILE *fd    = ::fopen(tmppath, "a");
            if (fd != NULL)
            {
                ::setvbuf(fd, NULL, _IONBF, BUFSIZ);
                ::fclose(stderr);
                stderr = fd;
            }
        #endif

            if (!fd)
            {
                ::fprintf(stderr, "Failed to open file %s, continuing redirect to STDERR\n", path);
                ::fflush(stderr);
            }
            ::free(tmppath);
        }

        int vprintf(const char *fmt, va_list args)
        {
            if (log_fd == NULL)
                return 0;

            int res = ::vfprintf(log_fd, fmt, args);
            ::fflush(log_fd);
            return res;
        }

        int printf(const char *fmt...)
        {
            va_list ap;
            va_start(ap, fmt);

            int r = vprintf(fmt, ap);

            va_end(ap);
            return r;
        }

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


