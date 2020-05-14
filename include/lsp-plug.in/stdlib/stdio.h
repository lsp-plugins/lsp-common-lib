/*
 * stdio.h
 *
 *  Created on: 4 апр. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_STDLIB_STDIO_H_
#define LSP_PLUG_IN_STDLIB_STDIO_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>
#include <stdio.h>

namespace lsp
{
#ifdef PLATFORM_WINDOWS
    typedef HANDLE              fhandle_t;

    LSP_COMMON_LIB_IMPORT
    int         vasprintf(char **strp, const char *fmt, va_list ap);

    LSP_COMMON_LIB_IMPORT
    int         asprintf(char **strp, const char *fmt, ...);

    LSP_COMMON_LIB_IMPORT
    int         fdsync(FILE *fd);

#endif /* PLATFORM_WINDOWS */

#ifdef PLATFORM_UNIX_COMPATIBLE
    typedef int                 fhandle_t;

    LSP_COMMON_LIB_IMPORT
    int         fdsync(FILE *fd);

#endif /* PLATFORM_UNIX_COMPATIBLE */
}

#endif /* LSP_PLUG_IN_STDLIB_STDIO_H_ */
