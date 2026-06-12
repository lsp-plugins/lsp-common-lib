/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
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

#ifndef LSP_PLUG_IN_STDLIB_STDIO_H_
#define LSP_PLUG_IN_STDLIB_STDIO_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>
#include <stdio.h>

namespace lsp
{
#ifdef PLATFORM_WINDOWS
    typedef void                   *fhandle_t;

    LSP_COMMON_LIB_PUBLIC
    int         vasprintf(char **strp, const char *fmt, va_list ap);

    LSP_COMMON_LIB_PUBLIC
    int         asprintf(char **strp, const char *fmt, ...);

    LSP_COMMON_LIB_PUBLIC
    int         fdsync(FILE *fd);

#endif /* PLATFORM_WINDOWS */

#ifdef PLATFORM_UNIX_COMPATIBLE
    typedef int                     fhandle_t;

    LSP_COMMON_LIB_PUBLIC
    int         fdsync(FILE *fd);

#endif /* PLATFORM_UNIX_COMPATIBLE */

    /**
     * Allocate memory for the string and perform formatted print to it.
     * The caller should free memory by issuing free() after use.
     *
     * @param fmt format string
     * @param ap argument list
     * @return pointer to allocated string or NULL
     */
    LSP_COMMON_LIB_PUBLIC
    char       *vstrfmt(const char *fmt, va_list ap);

    /**
     * Allocate memory for the string and perform formatted print to it.
     * The caller should free memory by issuing free() after use.
     *
     * @param fmt format string
     * @return pointer to allocated string or NULL
     */
    LSP_COMMON_LIB_PUBLIC
    char       *strfmt(const char *fmt, ...);

} /* namespace lsp */

#endif /* LSP_PLUG_IN_STDLIB_STDIO_H_ */
