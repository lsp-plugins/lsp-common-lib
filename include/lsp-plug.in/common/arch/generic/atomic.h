/*
 * Copyright (C) 2024 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2024 Vladimir Sadovnikov <sadko4u@gmail.com>
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

#define ATOMIC_STORE_DEF(type) \
    inline void atomic_store(type *ptr, type value) {               \
        __atomic_store_n(ptr, value, __ATOMIC_SEQ_CST);             \
    }

namespace lsp
{
    ATOMIC_STORE_DEF(int8_t)
    ATOMIC_STORE_DEF(uint8_t)
    ATOMIC_STORE_DEF(int16_t)
    ATOMIC_STORE_DEF(uint16_t)
    ATOMIC_STORE_DEF(int32_t)
    ATOMIC_STORE_DEF(uint32_t)
    ATOMIC_STORE_DEF(void *)

    #ifdef ARCH_64BIT
        ATOMIC_STORE_DEF(int64_t)
        ATOMIC_STORE_DEF(uint64_t)
    #endif /* ARCH_64BIT */
} /* namespace lsp */

#undef ATOMIC_STORE_DEF

#define ATOMIC_LOAD_DEF(type, ptrtype) \
    inline type atomic_load(ptrtype ptr) {                          \
        return __atomic_load_n(ptr, __ATOMIC_SEQ_CST);              \
    }

namespace lsp
{
    ATOMIC_LOAD_DEF(int8_t, int8_t *)
    ATOMIC_LOAD_DEF(int8_t, const int8_t *)
    ATOMIC_LOAD_DEF(uint8_t, uint8_t *)
    ATOMIC_LOAD_DEF(uint8_t, const uint8_t *)
    ATOMIC_LOAD_DEF(int16_t, int16_t *)
    ATOMIC_LOAD_DEF(int16_t, const int16_t *)
    ATOMIC_LOAD_DEF(uint16_t, uint16_t *)
    ATOMIC_LOAD_DEF(uint16_t, const uint16_t *)
    ATOMIC_LOAD_DEF(int32_t, int32_t *)
    ATOMIC_LOAD_DEF(int32_t, const int32_t *)
    ATOMIC_LOAD_DEF(uint32_t, uint32_t *)
    ATOMIC_LOAD_DEF(uint32_t, const uint32_t *)
    ATOMIC_LOAD_DEF(void *, void **)
    ATOMIC_LOAD_DEF(void *, void * const *)
    ATOMIC_LOAD_DEF(const void *, const void **)
    ATOMIC_LOAD_DEF(const void *, const void * const *)

    #ifdef ARCH_64BIT
        ATOMIC_LOAD_DEF(int64_t, int64_t *)
        ATOMIC_LOAD_DEF(int64_t, const int64_t *)
        ATOMIC_LOAD_DEF(uint64_t, uint64_t *)
        ATOMIC_LOAD_DEF(uint64_t, const uint64_t *)
    #endif /* ARCH_64BIT */
} /* namespace lsp */


#define ATOMIC_XCHG_DEF(type)                                       \
    inline type atomic_swap(type *ptr, type value) {                \
        return __atomic_exchange_n(ptr, value, __ATOMIC_SEQ_CST);   \
    }

namespace lsp
{
    ATOMIC_XCHG_DEF(int8_t)
    ATOMIC_XCHG_DEF(uint8_t)
    ATOMIC_XCHG_DEF(int16_t)
    ATOMIC_XCHG_DEF(uint16_t)
    ATOMIC_XCHG_DEF(int32_t)
    ATOMIC_XCHG_DEF(uint32_t)
    ATOMIC_XCHG_DEF(void *)

    #ifdef ARCH_64BIT
        ATOMIC_XCHG_DEF(int64_t)
        ATOMIC_XCHG_DEF(uint64_t)
    #endif /* ARCH_64BIT */
}

#undef ATOMIC_XCHG_DEF

#define ATOMIC_CAS_DEF(type)                                        \
    inline bool atomic_cas(type *ptr, type src, type rep) {         \
        return __sync_bool_compare_and_swap(ptr, src, rep);         \
    }

namespace lsp
{
    ATOMIC_CAS_DEF(int8_t)
    ATOMIC_CAS_DEF(uint8_t)
    ATOMIC_CAS_DEF(int16_t)
    ATOMIC_CAS_DEF(uint16_t)
    ATOMIC_CAS_DEF(int32_t)
    ATOMIC_CAS_DEF(uint32_t)
    ATOMIC_CAS_DEF(void *)

    #ifdef ARCH_64BIT
        ATOMIC_CAS_DEF(int64_t)
        ATOMIC_CAS_DEF(uint64_t)
    #endif /* ARCH_64BIT */
}

#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type)                                        \
    inline type atomic_add(type *ptr, type value) {                 \
        return __atomic_fetch_add(ptr, value, __ATOMIC_SEQ_CST);    \
    }

namespace lsp
{
    ATOMIC_ADD_DEF(int8_t)
    ATOMIC_ADD_DEF(uint8_t)
    ATOMIC_ADD_DEF(int16_t)
    ATOMIC_ADD_DEF(uint16_t)
    ATOMIC_ADD_DEF(int32_t)
    ATOMIC_ADD_DEF(uint32_t)

    #ifdef ARCH_64BIT
        ATOMIC_ADD_DEF(int64_t)
        ATOMIC_ADD_DEF(uint64_t)
    #endif /* ARCH_64BIT */
} /* namespace lsp */

#undef ATOMIC_ADD_DEF

//-----------------------------------------------------------------------------
// Atomic operations

#define LSP_ATOMIC_UNLOCKED     1
#define LSP_ATOMIC_LOCKED       0

namespace lsp
{
    template <class T>
    inline void atomic_init(T &lk)
    {
        atomic_store(
            fixed_int(&lk),
            fixed_int(T(LSP_ATOMIC_UNLOCKED))
        );
    }

    template <class T>
    inline bool atomic_trylock(T &lk)
    {
        return atomic_cas(
            fixed_int(&lk),
            fixed_int(T(LSP_ATOMIC_UNLOCKED)),
            fixed_int(T(LSP_ATOMIC_LOCKED))
        );
    }

    template <class T>
    inline T atomic_unlock(T &lk)
    {
        return T(atomic_swap(
            fixed_int(&lk),
            fixed_int(T(LSP_ATOMIC_UNLOCKED))
        ));
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_GENERIC_ATOMIC_H_ */
