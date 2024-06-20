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

#ifndef LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_
#define LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */

#define ATOMIC_LOAD_DEF(type, ptrtype, qsz, mod)                   \
    inline type atomic_load(ptrtype, ptr) \
    { \
        type tmp; \
        \
        ARCH_AARCH64_ASM \
        ( \
            __ASM_EMIT("ldar" qsz "      %" mod "[tmp], [%[ptr]]") \
            : [tmp] "=&r" (tmp) \
            : [ptr] "r" (ptr) \
            : "memory" \
        ); \
        return tmp; \
    }

namespace lsp
{
    ATOMIC_LOAD_DEF(int8_t, int8_t *, "sb", "w")
    ATOMIC_LOAD_DEF(int8_t, const int8_t *, "sb", "w")
    ATOMIC_LOAD_DEF(uint8_t, uint8_t *, "b", "w")
    ATOMIC_LOAD_DEF(uint8_t, const uint8_t *, "b", "w")
    ATOMIC_LOAD_DEF(int16_t, int16_t *, "sh", "w")
    ATOMIC_LOAD_DEF(int16_t, const int16_t *, "sh", "w")
    ATOMIC_LOAD_DEF(uint16_t, uint16_t *, "h", "w")
    ATOMIC_LOAD_DEF(uint16_t, const uint16_t *, "h", "w")
    ATOMIC_LOAD_DEF(int32_t, int32_t *, "", "w")
    ATOMIC_LOAD_DEF(int32_t, const int32_t *, "", "w")
    ATOMIC_LOAD_DEF(uint32_t, uint32_t *, "", "w")
    ATOMIC_LOAD_DEF(uint32_t, const uint32_t *, "", "w")
    ATOMIC_LOAD_DEF(int64_t, int64_t *, "", "x")
    ATOMIC_LOAD_DEF(int64_t, const int64_t *, "", "x")
    ATOMIC_LOAD_DEF(uint64_t, uint64_t *, "", "x")
    ATOMIC_LOAD_DEF(uint64_t, const uint64_t *, "", "x")
    ATOMIC_LOAD_DEF(void *, void **, "", "x")
    ATOMIC_LOAD_DEF(void *, void * const *, "", "x")
    ATOMIC_LOAD_DEF(const void *, const void **, "", "x")
    ATOMIC_LOAD_DEF(const void *, const void * const *, "", "x")
} /* namespace lsp */

#undef ATOMIC_LOAD_DEF

#define ATOMIC_STORE_DEF(type, qsz, mod)                   \
    inline void atomic_store(type *ptr, type value) \
    { \
        ARCH_AARCH64_ASM \
        ( \
            __ASM_EMIT("stlr" qsz "      %" mod "[value], [%[ptr]]") \
            : \
            : [ptr] "r" (ptr), [value] "r" (value) \
            : "memory" \
        ); \
    }

namespace lsp
{
    ATOMIC_STORE_DEF(int8_t,     "sb", "w")
    ATOMIC_STORE_DEF(uint8_t,    "b", "w")
    ATOMIC_STORE_DEF(int16_t,    "sh", "w")
    ATOMIC_STORE_DEF(uint16_t,   "h", "w")
    ATOMIC_STORE_DEF(int32_t,    "", "w")
    ATOMIC_STORE_DEF(uint32_t,   "", "w")
    ATOMIC_STORE_DEF(int64_t,    "", "x")
    ATOMIC_STORE_DEF(uint64_t,   "", "x")
    ATOMIC_STORE_DEF(void *,     "", "x")
} /* namespace lsp */

#undef ATOMIC_LOAD_DEF

#define ATOMIC_CAS_DEF(type, qsz, mod)                          \
    inline type atomic_cas(type *ptr, type exp, type rep) \
    { \
        type tmp; \
        \
        ARCH_AARCH64_ASM \
        ( \
            __ASM_EMIT("1:") \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" mod "[tmp], [%[ptr]]") \
            __ASM_EMIT("cmp             %" mod "[tmp], %" mod "[exp]") \
            __ASM_EMIT("mov             %" mod "[tmp], #0") \
            __ASM_EMIT("b.ne            2f")                                             /* jump if failed */ \
            __ASM_EMIT("stxr" qsz "     %w[tmp], %" mod "[rep], [%[ptr]]")               /* try to store replacement */ \
            __ASM_EMIT("cbnz            %w[tmp], 1b") /* repeat if failed */ \
            __ASM_EMIT("mov             %" mod "[tmp], #1") \
            __ASM_EMIT("2:") \
            : [tmp] "=&r" (tmp) \
            : [ptr] "r" (ptr), [exp] "r" (exp), [rep] "r" (rep) \
            : "cc", "memory" \
        ); \
        return tmp; \
    }

namespace lsp
{
    ATOMIC_CAS_DEF(int8_t, "b", "w")
    ATOMIC_CAS_DEF(uint8_t, "b", "w")
    ATOMIC_CAS_DEF(int16_t, "h", "w")
    ATOMIC_CAS_DEF(uint16_t, "h", "w")
    ATOMIC_CAS_DEF(int32_t, "", "w")
    ATOMIC_CAS_DEF(uint32_t, "", "w")
    ATOMIC_CAS_DEF(void *, "", "x")
    ATOMIC_CAS_DEF(int64_t, "", "x")
    ATOMIC_CAS_DEF(uint64_t, "", "x")
} /* namespace lsp */

#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type, qsz, mod) \
    inline type atomic_add(type *ptr, type value) \
    {                                                   \
        uint32_t tmp; \
        type sum, retval; \
        \
        ARCH_AARCH64_ASM                                \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" mod "[ret], [%[ptr]]") \
            __ASM_EMIT("add             %" mod "[sum], %" mod "[ret], %" mod "[src]") \
            __ASM_EMIT("stxr" qsz "     %w[tmp], %" mod "[sum], [%[ptr]]") \
            __ASM_EMIT("cbnz            %w[tmp], 1b") /* repeat if failed */ \
            : [tmp] "=&r" (tmp), \
              [sum] "=&r" (sum), \
              [ret] "=&r" (retval)  \
            : [ptr] "r" (ptr),  \
              [src] "r" (value) \
            : "memory", "cc"                            \
        );                                              \
        return retval; \
    }

namespace lsp
{
    ATOMIC_ADD_DEF(int8_t, "b", "w")
    ATOMIC_ADD_DEF(uint8_t, "b", "w")
    ATOMIC_ADD_DEF(int16_t, "h", "w")
    ATOMIC_ADD_DEF(uint16_t, "h", "w")
    ATOMIC_ADD_DEF(int32_t, "", "w")
    ATOMIC_ADD_DEF(uint32_t, "", "w")
    ATOMIC_ADD_DEF(int64_t, "", "x")
    ATOMIC_ADD_DEF(uint64_t, "", "x")
} /* namespace lsp */

#undef ATOMIC_ADD_DEF

#define ATOMIC_SWAP_DEF(type, qsz, mod) \
    inline type atomic_swap(type *ptr, type value) \
    {                                                   \
        uint32_t tmp; \
        type retval; \
        \
        ARCH_AARCH64_ASM                                \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" mod "[ret], [%[ptr]]") \
            __ASM_EMIT("stxr" qsz "     %w[tmp], %" mod "[value], [%[ptr]]") \
            __ASM_EMIT("cbnz            %w[tmp], 1b") /* repeat if failed */ \
            : [tmp] "=&r" (tmp), \
              [ret] "=&r" (retval)  \
            : [ptr] "r" (ptr),  \
              [value] "r" (value) \
            : "memory", "cc"                            \
        );                                              \
        return retval; \
    }

namespace lsp
{
    ATOMIC_SWAP_DEF(int8_t, "b", "w")
    ATOMIC_SWAP_DEF(uint8_t, "b", "w")
    ATOMIC_SWAP_DEF(int16_t, "h", "w")
    ATOMIC_SWAP_DEF(uint16_t, "h", "w")
    ATOMIC_SWAP_DEF(int32_t, "", "w")
    ATOMIC_SWAP_DEF(uint32_t, "", "w")
    ATOMIC_SWAP_DEF(int64_t, "", "x")
    ATOMIC_SWAP_DEF(uint64_t, "", "x")
} /* namespace lsp */

#undef ATOMIC_SWAP_DEF

//-----------------------------------------------------------------------------
// Atomic operations

#define LSP_ATOMIC_UNLOCKED     1
#define LSP_ATOMIC_LOCKED       0

namespace lsp
{
    template <class type_t>
        inline void atomic_init(type_t &lk) { lk = LSP_ATOMIC_UNLOCKED; }

    template <class type_t>
        inline type_t atomic_trylock(type_t &lk) { return atomic_cas(&lk, LSP_ATOMIC_UNLOCKED, LSP_ATOMIC_LOCKED); }

    template <class type_t>
        inline type_t atomic_unlock(type_t &lk) { return atomic_swap(&lk, LSP_ATOMIC_UNLOCKED); }
} /* namespace lsp */


#endif /* LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_ */
