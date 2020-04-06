/*
 * debug.h
 *
 *  Created on: 6 апр. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_DEBUG_H_
#define LSP_PLUG_IN_COMMON_DEBUG_H_

// Include <stdio.h> to perform debugging output
#include <lsp-plug.in/common/types.h>
#include <stdarg.h>

// Check trace level
#ifdef LSP_TRACE
    #define lsp_trace(msg, ...)         ::lsp::debug::printf("[TRC][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)

    // Debug is always turned on when trace is turned on
    #ifndef LSP_DEBUG
        #define LSP_DEBUG
    #endif /* LSP_DEBUG */
#else
    #define lsp_trace(msg, ...)
#endif /* LSP_TRACE */

// Check debug level
#ifdef LSP_DEBUG
    #define lsp_nprintf(msg, ...)       ::lsp::debug::printf(msg, ## __VA_ARGS__)
    #define lsp_nvprintf(msg, va_args)  ::lsp::debug::vprintf(msg, va_args)
    #define lsp_printf(msg, ...)        ::lsp::debug::printf(msg "\n", ## __VA_ARGS__)
    #define lsp_debug(msg, ...)         ::lsp::debug::printf("[DBG][%s:%4d] %s: " msg "\n", __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
    #define lsp_dumpf(s, fmt, p, n)     ::lsp::debug::dumpf(s, fmt, p, n)
    #define lsp_dumpb(s, p, sz)         ::lsp::debug::dumpb(s, p, sz)
#else
    #define lsp_nprintf(msg, ...)
    #define lsp_nvprintf(msg, va_args)
    #define lsp_printf(msg, ...)
    #define lsp_debug(msg, ...)
    #define lsp_dumpf(s, fmt, p, n)
    #define lsp_dumpb(s, p, sz)
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
    #define lsp_paranoia(...)           { __VA_ARGS__; }

    #define lsp_guard_assert(...)       __VA_ARGS__;
    #define lsp_assert(x)               if (!(x)) { lsp_error("Assertion failed: %s", #x); fflush(LSP_LOG_FD); }
    #define lsp_assert_msg(x, msg, ...)  \
            if (!(x))
                ::lsp::debug::printf("[ERR][%s:%4d] %s: Assertion failed: %s, nested message: " msg "\n", \
                    __FILE__, __LINE__, __FUNCTION__, #x, ## __VA_ARGS__);

#else
    #define lsp_paranoia(...)

    #define lsp_guard_assert(...)
    #define lsp_assert(x)
    #define lsp_assert_msg(x, ...)
#endif /* ASSERTIONS */

namespace lsp
{
    namespace debug
    {
        /**
         * Redirect log to the temporary file in the temporary directory
         * @param file file name (UTF-8)
         */
        void                redirect(const char *file);

        /**
         * Redirect log to the file located in the specified directoyr
         * @param path path to the temorary directory (UTF-8)
         * @param file
         */
        void                redirect(const char *path, const char *file);

        /** Output formatted string to the logging device
         *
         * @param fmt format
         */
        int                 printf(const char *fmt...);

        /** Output formatted string to the logging device
         *
         * @param fmt format
         * @param args additional set of arguments
         */
        int                 vprintf(const char *fmt, va_list args);

        /**
         * Dump floating-point values
         * @param s prefix string
         * @param fmt floating point number format
         * @param f array of floating-point numbers
         * @param n number of elements in array
         */
        void                dumpf(const char *s, const char *fmt, const float *f, size_t n);

        /**
         * Dump bytes
         * @param s prefix string
         * @param f pointer to array of bytes
         * @param n number of bytes in array
         */
        void                dumpb(const char *s, const void *b, size_t sz);
    }
}



#endif /* LSP_PLUG_IN_COMMON_DEBUG_H_ */
