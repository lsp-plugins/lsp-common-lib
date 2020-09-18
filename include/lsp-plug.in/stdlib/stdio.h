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
