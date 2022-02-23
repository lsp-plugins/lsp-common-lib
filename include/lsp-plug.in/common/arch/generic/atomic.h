/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 31 мар. 2020 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_GENERIC_ATOMIC_H_
#define LSP_PLUG_IN_COMMON_ARCH_GENERIC_ATOMIC_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */

#define ATOMIC_XCHG_DEF(type, extra) \
    inline extra type atomic_swap(extra type *ptr, type value) { \
        extra type *xptr = ptr; \
        while (true) { \
            extra type x = *xptr; \
            if (__sync_bool_compare_and_swap (ptr, x, value)) \
                return x; \
        } \
    }

namespace lsp
{
    ATOMIC_XCHG_DEF(int8_t, )
    ATOMIC_XCHG_DEF(int8_t, volatile)
    ATOMIC_XCHG_DEF(uint8_t, )
    ATOMIC_XCHG_DEF(uint8_t, volatile)
    ATOMIC_XCHG_DEF(int16_t, )
    ATOMIC_XCHG_DEF(int16_t, volatile)
    ATOMIC_XCHG_DEF(uint16_t, )
    ATOMIC_XCHG_DEF(uint16_t, volatile)
    ATOMIC_XCHG_DEF(int32_t, )
    ATOMIC_XCHG_DEF(int32_t, volatile)
    ATOMIC_XCHG_DEF(uint32_t, )
    ATOMIC_XCHG_DEF(uint32_t, volatile)
    ATOMIC_XCHG_DEF(void *, )
    ATOMIC_XCHG_DEF(void *, volatile)

    #ifdef ARCH_64BIT
        ATOMIC_XCHG_DEF(int64_t, )
        ATOMIC_XCHG_DEF(int64_t, volatile)
        ATOMIC_XCHG_DEF(uint64_t, )
        ATOMIC_XCHG_DEF(uint64_t, volatile)
    #endif /* ARCH_64BIT */
}

#undef ATOMIC_XCHG_DEF

#define ATOMIC_CAS_DEF(type, extra)                         \
    inline bool atomic_cas(extra type *ptr, type src, type rep) {  \
        return __sync_bool_compare_and_swap (ptr, src, rep); \
    }

namespace lsp
{
    ATOMIC_CAS_DEF(int8_t, )
    ATOMIC_CAS_DEF(int8_t, volatile)
    ATOMIC_CAS_DEF(uint8_t, )
    ATOMIC_CAS_DEF(uint8_t, volatile)
    ATOMIC_CAS_DEF(int16_t, )
    ATOMIC_CAS_DEF(int16_t, volatile)
    ATOMIC_CAS_DEF(uint16_t, )
    ATOMIC_CAS_DEF(uint16_t, volatile)
    ATOMIC_CAS_DEF(int32_t, )
    ATOMIC_CAS_DEF(int32_t, volatile)
    ATOMIC_CAS_DEF(uint32_t, )
    ATOMIC_CAS_DEF(uint32_t, volatile)
    ATOMIC_CAS_DEF(void *, )
    ATOMIC_CAS_DEF(void *, volatile)

    #ifdef ARCH_64BIT
        ATOMIC_CAS_DEF(int64_t, )
        ATOMIC_CAS_DEF(int64_t, volatile)
        ATOMIC_CAS_DEF(uint64_t, )
        ATOMIC_CAS_DEF(uint64_t, volatile)
    #endif /* ARCH_64BIT */
}

#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type, extra) \
    inline type atomic_add(extra type *ptr, type value) { \
        return __sync_fetch_and_add(ptr, value); \
    }

namespace lsp
{
    ATOMIC_ADD_DEF(int8_t, )
    ATOMIC_ADD_DEF(int8_t, volatile)
    ATOMIC_ADD_DEF(uint8_t, )
    ATOMIC_ADD_DEF(uint8_t, volatile)
    ATOMIC_ADD_DEF(int16_t, )
    ATOMIC_ADD_DEF(int16_t, volatile)
    ATOMIC_ADD_DEF(uint16_t, )
    ATOMIC_ADD_DEF(uint16_t, volatile)
    ATOMIC_ADD_DEF(int32_t, )
    ATOMIC_ADD_DEF(int32_t, volatile)
    ATOMIC_ADD_DEF(uint32_t, )
    ATOMIC_ADD_DEF(uint32_t, volatile)

    #ifdef ARCH_64BIT
        ATOMIC_ADD_DEF(int64_t, )
        ATOMIC_ADD_DEF(int64_t, volatile)
        ATOMIC_ADD_DEF(uint64_t, )
        ATOMIC_ADD_DEF(uint64_t, volatile)
    #endif /* ARCH_64BIT */
}

#undef ATOMIC_ADD_DEF

//-----------------------------------------------------------------------------
// Atomic operations
namespace lsp
{
    template <class type_t>
        inline void atomic_init(type_t &lk) { lk = 1; }

    template <class type_t>
        inline bool atomic_trylock(type_t &lk) { return atomic_cas(&lk, 1, 0); }

    template <class type_t>
        inline type_t atomic_unlock(type_t &lk) { return atomic_swap(&lk, 1); }
}

#endif /* LSP_PLUG_IN_COMMON_ARCH_GENERIC_ATOMIC_H_ */
