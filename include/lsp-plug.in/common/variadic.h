/*
 * Copyright (C) 2022 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2022 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 14 окт. 2022 г.
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

#ifndef LSP_PLUG_IN_COMMON_VARIADIC_H_
#define LSP_PLUG_IN_COMMON_VARIADIC_H_

#include <lsp-plug.in/common/version.h>

namespace lsp
{
    // lsp::remove_reference
    template <class T>
    struct remove_reference
    {
        typedef T type;
    };

    template <class T>
    struct remove_reference<T&>
    {
        typedef T type;
    };

    template <class T>
    struct remove_reference<T&&>
    {
        typedef T type;
    };

    // lsp::remove_const
    template<class T>
    struct remove_const
    {
        typedef T type;
    };

    template<class T>
    struct remove_const<const T>
    {
        typedef T type;
    };

    template <class T>
    struct unconst_ptr_type
    {
        using type = typename remove_const<T>::type;
        static inline type * cast(type * value)         { return static_cast<type *>(value); }
        static inline type * cast(const type * value)   { return const_cast<type *>(value);  }
    };

    // lsp::unconst_ptr
    template <typename T>
    typename unconst_ptr_type<T>::type * unconst_ptr(T * t) noexcept
    {
        return unconst_ptr_type<T>::cast(t);
    }
    
    // lsp::move
    template <typename T>
    typename remove_reference<T>::type && move(T && t) noexcept
    {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }

    // lsp::forward
    template<typename T>
    constexpr T && forward(typename remove_reference<T>::type && args) noexcept
    {
        return static_cast<T &&>(args);
    }

    template<typename T>
    constexpr T && forward(typename remove_reference<T>::type & args) noexcept
    {
        return static_cast<T &&>(args);
    }

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_VARIADIC_H_ */
