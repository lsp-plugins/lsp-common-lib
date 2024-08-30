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
#include <lsp-plug.in/common/types.h>
#include <locale.h>
#include <string.h>

#define SET_LOCALE_MANGLE2(prefix, postfix) prefix ## _ ## postfix
#define SET_LOCALE_MANGLE1(prefix, postfix) SET_LOCALE_MANGLE2(prefix, postfix)
#define SET_LOCALE_MANGLE(var) SET_LOCALE_MANGLE1(var, __COUNTER__)

#ifdef PLATFORM_WINDOWS
    #define SET_LOCALE_SCOPED_VAR(state, old, old_len, buf, lc, value) \
        int state = _configthreadlocale(_ENABLE_PER_THREAD_LOCALE); \
        char *old = setlocale(lc, NULL); \
        if (old != NULL) \
        { \
            size_t old_len = strlen(old) + 1; \
            char *buf = static_cast<char *>(alloca(old_len)); \
            memcpy(buf, old, old_len); \
            old = buf; \
        } \
        setlocale(lc, value); \
        lsp_finally { \
            if (old != NULL) \
                ::setlocale(lc, old); \
            if (state >= 0) \
                _configthreadlocale(state); \
        }

#define SET_LOCALE_SCOPED(lc, value) SET_LOCALE_SCOPED_VAR( \
    SET_LOCALE_MANGLE(__state), \
    SET_LOCALE_MANGLE(__old), \
    SET_LOCALE_MANGLE(__len), \
    SET_LOCALE_MANGLE(__buf), \
    lc, \
    value)

#else

#define SET_LOCALE_SCOPED_VAR(old, new, lc, value) \
    locale_t old = ::lsp::detail::INVALID_LOCALE; \
    locale_t new = ::lsp::detail::create_locale(lc, value); \
    if (new != ::lsp::detail::INVALID_LOCALE) \
        old = uselocale(new); \
    lsp_finally { \
        if (old != ::lsp::detail::INVALID_LOCALE) \
            uselocale(old); \
        if (new != ::lsp::detail::INVALID_LOCALE) \
            freelocale(new); \
    }

#define SET_LOCALE_SCOPED(lc, value) SET_LOCALE_SCOPED_VAR( \
    SET_LOCALE_MANGLE(__old), \
    SET_LOCALE_MANGLE(__new), \
    lc, \
    value)

namespace lsp
{
    namespace detail
    {
        constexpr locale_t INVALID_LOCALE = (locale_t)0;

        /**
         * Create locale object based on locale type and name
         * @param type locale type
         * @param name locale name
         * @return created locale object
         */
        LSP_COMMON_LIB_PUBLIC
        locale_t  create_locale(int type, const char *name);
    } /* namespace detail */
} /* namespace lsp */

#endif /* PLATFORM_WINDOWS */


#endif /* LSP_PLUG_IN_STDLIB_LOCALE_H_ */
