/*
 * Copyright (C) 2023 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2023 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 19 нояб. 2023 г.
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

#ifndef LSP_PLUG_IN_STDLIB_LOCALE_H_
#define LSP_PLUG_IN_STDLIB_LOCALE_H_

#include <lsp-plug.in/common/version.h>

#include <lsp-plug.in/common/finally.h>
#include <locale.h>

#define SET_LOCALE_MANGLE2(prefix, postfix) prefix ## _ ## postfix
#define SET_LOCALE_MANGLE1(prefix, postfix) SET_LOCALE_MANGLE2(prefix, postfix)
#define SET_LOCALE_MANGLE(var) SET_LOCALE_MANGLE1(var, __COUNTER__)

#define SET_LOCALE_SCOPED_VAR(tmp_var, lc, value) \
    char *tmp_var = setlocale(lc, NULL); \
    if (tmp_var != NULL) \
    { \
        size_t ___len = strlen(tmp_var) + 1; \
        char *___copy = static_cast<char *>(alloca(___len)); \
        memcpy(___copy, tmp_var, ___len); \
        tmp_var = ___copy; \
    } \
    setlocale(lc, value); \
    lsp_finally { \
        if (tmp_var != NULL) \
            ::setlocale(LC_NUMERIC, tmp_var); \
    }

#define SET_LOCALE_SCOPED(lc, value) SET_LOCALE_SCOPED_VAR(SET_LOCALE_MANGLE(tmp_var), lc, value)



#endif /* LSP_PLUG_IN_STDLIB_LOCALE_H_ */
