/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 23 янв. 2026 г.
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

#ifndef LSP_PLUG_IN_COMMON_UTILITY_H_
#define LSP_PLUG_IN_COMMON_UTILITY_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/variadic.h>

//------------------------------------------------------------------------------
// Library exports, for built-in modules there are no exports
namespace lsp
{
    template <class T>
    inline void swap(T &a, T &b)
    {
        T tmp   = lsp::move(a);
        a       = lsp::move(b);
        b       = lsp::move(tmp);
    }

    template <class T>
    inline T *release(T * &a)
    {
        T *tmp = a;
        a = NULL;
        return tmp;
    }

    template <class A, class B>
    inline A lsp_max(A a, B b)
    {
        return (a > b) ? a : b;
    }

    template <class A, class B, class C>
    inline A lsp_max(A a, B b, C c)
    {
        if ((a > b) && (a > c))
            return a;
        return (b > c) ? b : c;
    }

    template <class A, class B, class C, class D>
    inline A lsp_max(A a, B b, C c, D d)
    {
        return lsp_max(lsp_max(a, b), lsp_max(c, d));
    }

    template <class A, class B>
    inline A lsp_min(A a, B b)
    {
        return (a < b) ? a : b;
    }

    template <class A, class B, class C>
    inline A lsp_min(A a, B b, C c)
    {
        if ((a < b) && (a < c))
            return a;
        return (b < c) ? b : c;
    }

    template <class A, class B, class C, class D>
    inline A lsp_min(A a, B b, C c, D d)
    {
        return lsp_min(lsp_min(a, b), lsp_min(c, d));
    }

    template <class A, class B, class C>
    inline A lsp_limit(A a, B min, C max)
    {
        return (a < min) ? min : ((a > max) ? max : a);
    }

    template <class A, class B, class C>
    inline A lsp_xlimit(A a, B min, C max)
    {
        if (min < max)
            return (a < min) ? min : ((a > max) ? max : a);

        return (a < max) ? max : ((a > min) ? min : a);
    }

    template <class T>
    inline T lsp_abs(T a)
    {
        return (a < 0) ? -a : a;
    }

    template <class S, class F>
    inline S lsp_setflag(S bits, F flag, bool value)
    {
        return (value) ? bits | flag : bits & (~flag);
    }

    template <class T>
    inline T * release_ptr(T * & value)
    {
        T *res  = value;
        value   = nullptr;
        return res;
    }

    LSP_COMMON_LIB_PUBLIC
    int version_cmp(const version_t *a, const version_t *b);

    LSP_COMMON_LIB_PUBLIC
    int version_cmp(const version_t &a, const version_t &b);

    LSP_COMMON_LIB_PUBLIC
    bool version_copy(version_t *dst, const version_t *src);

    LSP_COMMON_LIB_PUBLIC
    void version_destroy(version_t *version);
} /* namespace lsp */


#endif /* LSP_PLUG_IN_COMMON_UTILITY_H_ */
