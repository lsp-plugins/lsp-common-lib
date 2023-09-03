/*
 * Copyright (C) 2023 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2023 Vladimir Sadovnikov <sadko4u@gmail.com>
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
#include <lsp-plug.in/stdlib/stdlib.h>
#include <lsp-plug.in/stdlib/string.h>
#include <unistd.h>

namespace lsp
{
    namespace debug
    {
        static FILE *log_fd = stderr;

        LSP_COMMON_LIB_PUBLIC
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

        LSP_COMMON_LIB_PUBLIC
        void redirect(const char *path, const char *file)
        {
            if (log_fd != stderr)
                return;

            char *tmppath = NULL;
            int n = asprintf(&tmppath, "%s" FILE_SEPARATOR_S "%s", path, file);
            if ((n < 0) || (tmppath == NULL))
                return;

            ::fprintf(log_fd, "Log data will be written to file: %s\n", path);
            ::fflush(log_fd);

            FILE *fd  = ::fopen(tmppath, "a");
            if (fd == NULL)
            {
                ::fprintf(stderr, "Failed to open file %s, continuing redirect to STDERR\n", path);
                ::fflush(stderr);
            }
            else
                log_fd = fd;

            ::free(tmppath);
        }

        LSP_COMMON_LIB_PUBLIC
        int vprintf(const char *fmt, va_list args)
        {
            if (log_fd == NULL)
                return 0;

            int res = ::vfprintf(log_fd, fmt, args);
            ::fflush(log_fd);
            return res;
        }

        LSP_COMMON_LIB_PUBLIC
        int printf(const char *fmt...)
        {
            va_list ap;
            va_start(ap, fmt);

            int r = vprintf(fmt, ap);

            va_end(ap);
            return r;
        }

        LSP_COMMON_LIB_PUBLIC
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

        LSP_COMMON_LIB_PUBLIC
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

        //---------------------------------------------------------------------
        static const char *hex_digits = "0123456789abcdef";

        static inline size_t num_ascii_characters(lsp_utf16_t c)
        {
            if (c < 0x80)
                return 1;
            return (c < 0x100) ? 4 : 6; // \x12 or \u1234
        }

        static inline size_t num_ascii_characters(lsp_utf32_t c)
        {
            if (c < 0x100)
                return (c < 0x80) ? 1 : 4; // char or \x12

            size_t nd = 4; // \U12
            c       >>= 8;
            if (c & 0xff0000)
            {
                c     >>= 16;
                nd     += 4;
            }
            else if (c & 0xff00)
            {
                c     >>= 8;
                nd     += 2;
            }
            nd     += (c >= 0x10) ? 2 : 1;

            return nd;
        }

        static inline char *make_string(const char *src)
        {
            return strdup(src);
        }

        static char *make_string(const lsp_utf16_t *src)
        {
            // Estimate the length of the result string
            size_t n    = 0;
            for (const lsp_utf16_t *s = src; *s != '\0'; ++s)
                n          += num_ascii_characters(*s);

            // Allocate the data
            char *text  = static_cast<char *>(malloc(n + 1));
            if (text == NULL)
                return NULL;

            // Perform string encoding
            char *dst   = text;
            for (const lsp_utf16_t *s = src; *s != '\0'; ++s)
            {
                lsp_utf16_t c = *s;
                if (c < 0x80)
                    *(dst++)    = char(c);
                else if (c < 0x100)
                {
                    dst[0]      = '\\';
                    dst[1]      = 'x';
                    dst[2]      = hex_digits[(c >> 4) & 0xf];
                    dst[3]      = hex_digits[c & 0xf];
                    dst        += 4;
                }
                else
                {
                    dst[0]      = '\\';
                    dst[1]      = 'u';
                    dst[2]      = hex_digits[(c >> 12) & 0xf];
                    dst[3]      = hex_digits[(c >> 8) & 0xf];
                    dst[4]      = hex_digits[(c >> 4) & 0xf];
                    dst[5]      = hex_digits[c & 0xf];
                    dst        += 6;
                }
            }

            // End of string character
            *dst        = '\0';

            return text;
        }

        static char *make_string(const lsp_utf32_t *src)
        {
            // Estimate the length of the result string
            size_t n    = 0;
            for (const lsp_utf32_t *s = src; *s != '\0'; ++s)
                n          += num_ascii_characters(*s);

            // Allocate the data
            char *text  = static_cast<char *>(malloc(n + 1));
            if (text == NULL)
                return NULL;

            // Perform string encoding
            char *dst   = text;
            for (const lsp_utf32_t *s = src; *s != '\0'; ++s)
            {
                lsp_utf32_t c = *s;
                if (c < 0x80)
                    *(dst++)    = char(c);
                else if (c < 0x100)
                {
                    dst[0]      = '\\';
                    dst[1]      = 'x';
                    dst[2]      = hex_digits[(c >> 4) & 0xf];
                    dst[3]      = hex_digits[c & 0xf];
                    dst        += 4;
                }
                else
                {
                    dst[0]      = '\\';
                    dst[1]      = 'U';
                    dst        += 2;

                    // Encode the hex digit representing the UTF codepoint
                    ssize_t sh  = 28;
                    while (!(c & (0xf << sh)))
                        sh      -= 4;
                    while (sh >= 0)
                    {
                        *(dst++)    = hex_digits[(c >> sh) & 0xf];
                        sh         -= 4;
                    }
                }
            }

            // End of string character
            *dst        = '\0';

            return text;
        }

        //---------------------------------------------------------------------
        log_string::log_string(const char *src)
        {
            text        = make_string(src);
        }

        log_string::log_string(const lsp_utf16_t *src)
        {
            text        = make_string(src);
        }

        log_string::log_string(const lsp_utf32_t *src)
        {
            text        = make_string(src);
        }

        log_string::log_string(const log_string & src)
        {
            text        = (src.text != NULL) ? strdup(src.text) : NULL;
        }

        log_string::log_string(const log_string * src)
        {
            text        = (src->text != NULL) ? strdup(src->text) : NULL;
        }

        log_string::log_string(log_string && src)
        {
            text        = src.text;
            src.text    = NULL;
        }

        log_string::~log_string()
        {
            if (text != NULL)
            {
                free(text);
                text        = NULL;
            }
        }

        log_string & log_string::operator = (const char *src)
        {
            if (text != NULL)
                free(text);
            text        = make_string(src);
            return *this;
        }

        log_string & log_string::operator = (const lsp_utf16_t *src)
        {
            if (text != NULL)
                free(text);
            text        = make_string(src);
            return *this;
        }

        log_string & log_string::operator = (const lsp_utf32_t *src)
        {
            if (text != NULL)
                free(text);
            text        = make_string(src);
            return *this;
        }

        log_string & log_string::operator = (const log_string & src)
        {
            if (this == &src)
                return *this;

            if (text != NULL)
                free(text);
            text        = (src.text != NULL) ? strdup(src.text) : NULL;
            return *this;
        }

        log_string & log_string::operator = (log_string && src)
        {
            if (this == &src)
                return *this;

            if (text != NULL)
                free(text);
            text        = src.text;
            src.text    = NULL;
            return *this;
        }

        void log_string::swap(log_string &src)
        {
            lsp::swap(text, src.text);
        }

        void log_string::swap(log_string *src)
        {
            lsp::swap(text, src->text);
        }

    } /* namespace debug */
} /* namespace lsp */


