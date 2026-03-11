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

#ifndef LSP_PLUG_IN_COMMON_FIXED_INT_H_
#define LSP_PLUG_IN_COMMON_FIXED_INT_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

namespace lsp
{
#if defined(ARCH_32BIT)
    typedef uint32_t            fixed_size_t;
    typedef int32_t             fixed_ssize_t;
#elif defined(ARCH_64BIT)
    typedef uint64_t            fixed_size_t;
    typedef int64_t             fixed_ssize_t;
#else /* fall-back */
    typedef size_t              fixed_size_t;
    typedef ssize_t             fixed_ssize_t;
#endif /* ARCH_32BIT */

    template <int size, bool S> struct fixed_int_alias_t        { };
    template <typename T> struct fixed_int_type_t               { };

    template <> struct fixed_int_alias_t<1, true>               { typedef int8_t type;      };
    template <> struct fixed_int_alias_t<2, true>               { typedef int16_t type;     };
    template <> struct fixed_int_alias_t<4, true>               { typedef int32_t type;     };
    template <> struct fixed_int_alias_t<8, true>               { typedef int64_t type;     };
    template <> struct fixed_int_alias_t<1, false>              { typedef uint8_t type;     };
    template <> struct fixed_int_alias_t<2, false>              { typedef uint16_t type;    };
    template <> struct fixed_int_alias_t<4, false>              { typedef uint32_t type;    };
    template <> struct fixed_int_alias_t<8, false>              { typedef uint64_t type;    };

    template <> struct fixed_int_type_t<char> : public fixed_int_alias_t<sizeof(char), char(0xff) < 0> {};
    template <> struct fixed_int_type_t<signed char> : public fixed_int_alias_t<sizeof(signed char), true> {};
    template <> struct fixed_int_type_t<signed short> : public fixed_int_alias_t<sizeof(signed short), true> {};
    template <> struct fixed_int_type_t<signed int> : public fixed_int_alias_t<sizeof(signed int), true> {};
    template <> struct fixed_int_type_t<signed long> : public fixed_int_alias_t<sizeof(signed long), true> {};
    template <> struct fixed_int_type_t<signed long long> : public fixed_int_alias_t<sizeof(signed long long), true> {};
    template <> struct fixed_int_type_t<unsigned char> : public fixed_int_alias_t<sizeof(unsigned char), false> {};
    template <> struct fixed_int_type_t<unsigned short> : public fixed_int_alias_t<sizeof(unsigned short), false> {};
    template <> struct fixed_int_type_t<unsigned int> : public fixed_int_alias_t<sizeof(unsigned int), false> {};
    template <> struct fixed_int_type_t<unsigned long> : public fixed_int_alias_t<sizeof(unsigned long), false> {};
    template <> struct fixed_int_type_t<unsigned long long> : public fixed_int_alias_t<sizeof(unsigned long long), false> {};

    /**
     * Safe size-matching conversion of integral type to one of intN_t/uintN_t types without losing precision.
     * This is usual for systems where size_t is defined in some strange way like in MacOS.
     *
     * @param value value to convert
     * @return converted value
     */
    template <typename T>
    constexpr inline typename fixed_int_type_t<T>::type fixed_int(T value)
    {
        return typename fixed_int_type_t<T>::type(value);
    }

    /**
     * Safe size-matching conversion of integral type pointer to one of intN_t/uintN_t pointer types without losing precision.
     * This is usual for systems where size_t is defined in some strange way like in MacOS.
     *
     * @param value value to convert
     * @return converted value
     */
    template <typename T>
    constexpr inline typename fixed_int_type_t<T>::type *fixed_int(T *value)
    {
        return reinterpret_cast<typename fixed_int_type_t<T>::type *>(value);
    }

    /**
     * Safe size-matching conversion of integral type pointer to one of intN_t/uintN_t pointer types without losing precision.
     * This is usual for systems where size_t is defined in some strange way like in MacOS.
     *
     * @param value value to convert
     * @return converted value
     */
    template <typename T>
    constexpr inline const typename fixed_int_type_t<T>::type * fixed_int(const T *value)
    {
        return reinterpret_cast<const typename fixed_int_type_t<T>::type *>(value);
    }

} /* namespace lsp */



#endif /* LSP_PLUG_IN_COMMON_FIXED_INT_H_ */
