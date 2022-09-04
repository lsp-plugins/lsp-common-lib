/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 6 апр. 2020 г.
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

#ifndef LSP_PLUG_IN_COMMON_DEBUG_H_
#define LSP_PLUG_IN_COMMON_DEBUG_H_

// Include <stdio.h> to perform debugging output
#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>
#include <stdarg.h>

#define LSP_DEBUG_STUB_CALL             do {} while(0)

// Check trace level
#ifdef LSP_TRACE
    #define lsp_trace(msg, ...)         ::lsp::debug::printf("[TRC][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)

    // Debug is always turned on when trace is turned on
    #ifndef LSP_DEBUG
        #define LSP_DEBUG
    #endif /* LSP_DEBUG */

    #define IF_TRACE(...)               __VA_ARGS__
#else
    #define lsp_trace(msg, ...)         LSP_DEBUG_STUB_CALL

    #define IF_TRACE(...)
#endif /* LSP_TRACE */

// Check debug level
#ifdef LSP_DEBUG
    #define lsp_nprintf(msg, ...)       ::lsp::debug::printf(msg, ## __VA_ARGS__)
    #define lsp_nvprintf(msg, va_args)  ::lsp::debug::vprintf(msg, va_args)
    #define lsp_printf(msg, ...)        ::lsp::debug::printf(msg "\n", ## __VA_ARGS__)
    #define lsp_debug(msg, ...)         ::lsp::debug::printf("[DBG][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
    #define lsp_dumpf(s, fmt, p, n)     ::lsp::debug::dumpf(s, fmt, p, n)
    #define lsp_dumpb(s, p, sz)         ::lsp::debug::dumpb(s, p, sz)

    #define IF_DEBUG(...)               __VA_ARGS__
#else
    #define lsp_nprintf(msg, ...)       LSP_DEBUG_STUB_CALL
    #define lsp_nvprintf(msg, va_args)  LSP_DEBUG_STUB_CALL
    #define lsp_printf(msg, ...)        LSP_DEBUG_STUB_CALL
    #define lsp_debug(msg, ...)         LSP_DEBUG_STUB_CALL
    #define lsp_dumpf(s, fmt, p, n)     LSP_DEBUG_STUB_CALL
    #define lsp_dumpb(s, p, sz)         LSP_DEBUG_STUB_CALL

    #define IF_DEBUG(...)
#endif /* LSP_DEBUG */

#ifdef LSP_DEBUG
    #define lsp_error(msg, ...)         ::lsp::debug::printf("[ERR][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
    #define lsp_warn(msg, ...)          ::lsp::debug::printf("[WRN][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
    #define lsp_info(msg, ...)          ::lsp::debug::printf("[INF][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
#else
    #define lsp_error(msg, ...)         ::lsp::debug::printf("[ERR] " msg "\n", ## __VA_ARGS__)
    #define lsp_warn(msg, ...)          ::lsp::debug::printf("[WRN] " msg "\n", ## __VA_ARGS__)
    #define lsp_info(msg, ...)          ::lsp::debug::printf("[INF] " msg "\n", ## __VA_ARGS__)
#endif /* LSP_DEBUG */

// Define assertions
#ifdef LSP_DEBUG
    #define lsp_paranoia(...)           do { __VA_ARGS__; } while (0);

    #define lsp_guard_assert(...)       __VA_ARGS__;
    #define lsp_assert(x)               if (!(x)) lsp_error("Assertion failed: %s", #x);
    #define lsp_assert_msg(x, msg, ...)  \
            if (!(x)) \
                ::lsp::debug::printf("[ERR][%s:%4d] %s: Assertion failed: %s, nested message: " msg "\n", \
                    __FILE__, __LINE__, __FUNCTION__, #x, ## __VA_ARGS__);

#else
    #define lsp_paranoia(...)           LSP_DEBUG_STUB_CALL

    #define lsp_guard_assert(...)       LSP_DEBUG_STUB_CALL
    #define lsp_assert(x)               LSP_DEBUG_STUB_CALL
    #define lsp_assert_msg(x, ...)      LSP_DEBUG_STUB_CALL
#endif /* ASSERTIONS */

namespace lsp
{
    namespace debug
    {
        /**
         * Redirect log to the temporary file in the temporary directory
         * @param file file name (UTF-8)
         */
        LSP_COMMON_LIB_PUBLIC
        void                redirect(const char *file);

        /**
         * Redirect log to the file located in the specified directoyr
         * @param path path to the temorary directory (UTF-8)
         * @param file
         */
        LSP_COMMON_LIB_PUBLIC
        void                redirect(const char *path, const char *file);

        /** Output formatted string to the logging device
         *
         * @param fmt format
         */
        LSP_COMMON_LIB_PUBLIC
        int                 printf(const char *fmt...);

        /** Output formatted string to the logging device
         *
         * @param fmt format
         * @param args additional set of arguments
         */
        LSP_COMMON_LIB_PUBLIC
        int                 vprintf(const char *fmt, va_list args);

        /**
         * Dump floating-point values
         * @param s prefix string
         * @param fmt floating point number format
         * @param f array of floating-point numbers
         * @param n number of elements in array
         */
        LSP_COMMON_LIB_PUBLIC
        void                dumpf(const char *s, const char *fmt, const float *f, size_t n);

        /**
         * Dump bytes
         * @param s prefix string
         * @param f pointer to array of bytes
         * @param n number of bytes in array
         */
        LSP_COMMON_LIB_PUBLIC
        void                dumpb(const char *s, const void *b, size_t sz);
    }
}



#endif /* LSP_PLUG_IN_COMMON_DEBUG_H_ */
