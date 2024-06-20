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

#ifndef LSP_PLUG_IN_COMMON_ARCH_X86_ATOMIC_H_
#define LSP_PLUG_IN_COMMON_ARCH_X86_ATOMIC_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */

#define ATOMIC_LOAD_DEF(type)                           \
    inline type atomic_load(type *ptr)                  \
    {                                                   \
        type value;                                     \
        ARCH_X86_ASM                                    \
        (                                               \
            __ASM_EMIT("mov     (%[ptr]), %[value]")    \
            : [value] "=&r"(value)                      \
            : [ptr] "r" (ptr)                           \
            : "memory"                                  \
        );                                              \
        return value;                                   \
    }

namespace lsp
{
    ATOMIC_LOAD_DEF(int8_t)
    ATOMIC_LOAD_DEF(uint8_t)
    ATOMIC_LOAD_DEF(int16_t)
    ATOMIC_LOAD_DEF(uint16_t)
    ATOMIC_LOAD_DEF(int32_t)
    ATOMIC_LOAD_DEF(uint32_t)
    ATOMIC_LOAD_DEF(void *)

    #ifdef ARCH_X86_64
        ATOMIC_LOAD_DEF(int64_t)
        ATOMIC_LOAD_DEF(uint64_t)
    #endif /* ARCH_X86_64 */

} /* namespace lsp */

#undef ATOMIC_LOAD_DEF

#define ATOMIC_STORE_DEF(type)                          \
    inline void atomic_store(type *ptr, type value)     \
    {                                                   \
        ARCH_X86_ASM                                    \
        (                                               \
            __ASM_EMIT("mov     %[value], (%[ptr])")    \
            :                                           \
            : [ptr] "r" (ptr), [value] "r" (value)      \
            : "memory"                                  \
        );                                              \
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

    #ifdef ARCH_X86_64
        ATOMIC_STORE_DEF(int64_t)
        ATOMIC_STORE_DEF(uint64_t)
    #endif /* ARCH_X86_64 */

} /* namespace lsp */

#undef ATOMIC_STORE_DEF

#define ATOMIC_XCHG_DEF(type)                           \
    inline type atomic_swap(type *ptr, type value)      \
    {                                                   \
        ARCH_X86_ASM                                    \
        (                                               \
            __ASM_EMIT("lock")                          \
            __ASM_EMIT("xchg    %[value], (%[ptr])")    \
            : [value] "+r"(value)                       \
            : [ptr] "r" (ptr)                           \
            : "memory", "cc"                            \
        );                                              \
        return value;                                   \
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

    #ifdef ARCH_X86_64
        ATOMIC_XCHG_DEF(int64_t)
        ATOMIC_XCHG_DEF(uint64_t)
    #endif /* ARCH_X86_64 */

} /* namespace lsp */

#undef ATOMIC_XCHG_DEF

#define ATOMIC_CAS_DEF(type)                     \
    inline bool atomic_cas(type *ptr, type src, type rep)   \
    {                                                   \
        bool res;                                       \
        ARCH_X86_ASM                                    \
        (                                               \
            __ASM_EMIT("cmp     %[src], (%[ptr])")      \
            __ASM_EMIT("jne     2f")                    \
            __ASM_EMIT("lock")                          \
            __ASM_EMIT("cmpxchg %[rep], (%[ptr])")      \
            __ASM_EMIT("2:")                            \
            : [res] "=@ccz" (res)                       \
            : [src] "a" (src),                          \
              [ptr] "r" (ptr),                          \
              [rep] "r" (rep)                           \
            : "memory", "cc"                            \
        );                                              \
        return res; \
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

    #ifdef ARCH_X86_64
        ATOMIC_CAS_DEF(int64_t)
        ATOMIC_CAS_DEF(uint64_t)
    #endif /* ARCH_X86_64 */

} /* namespace lsp */
#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type) \
    inline type atomic_add(type *ptr, type value)       \
    {                                                   \
        ARCH_X86_ASM                                    \
        (                                               \
            __ASM_EMIT("lock")                          \
            __ASM_EMIT("xadd %[src], (%[ptr])")         \
            : [src] "+r" (value)                        \
            : [ptr] "r" (ptr)                           \
            : "memory", "cc"                            \
        );                                              \
        return value; \
    }

namespace lsp
{
    ATOMIC_ADD_DEF(int8_t)
    ATOMIC_ADD_DEF(uint8_t)
    ATOMIC_ADD_DEF(int16_t)
    ATOMIC_ADD_DEF(uint16_t)
    ATOMIC_ADD_DEF(int32_t)
    ATOMIC_ADD_DEF(uint32_t)

    #ifdef ARCH_X86_64
        ATOMIC_ADD_DEF(int64_t)
        ATOMIC_ADD_DEF(uint64_t)
    #endif /* ARCH_X86_64 */

} /* namespace lsp */

#undef ATOMIC_ADD_DEF

//-----------------------------------------------------------------------------
// Atomic operations

#define LSP_ATOMIC_UNLOCKED     1
#define LSP_ATOMIC_LOCKED       0

namespace lsp
{
    template <class type_t>
    inline void atomic_init(type_t &lk)         { lk = LSP_ATOMIC_UNLOCKED; }

    template <class type_t>
    inline type_t atomic_trylock(type_t &lk)    { return atomic_swap(&lk, LSP_ATOMIC_LOCKED); }

    template <class type_t>
    inline type_t atomic_unlock(type_t &lk)     { return atomic_swap(&lk, LSP_ATOMIC_UNLOCKED); }

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_X86_ATOMIC_H_ */
