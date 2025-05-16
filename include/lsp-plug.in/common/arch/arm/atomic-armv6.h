/*
 * Copyright (C) 2025 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2025 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 4 мар. 2025 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_ARMV6_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_ARMV6_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */

namespace lsp
{
    extern uint32_t atomic_lock_barrier;
} /* namespace lsp */

#define ATOMIC_LOAD_DEF(type, ptrtype, cmd) \
    inline type atomic_load(ptrtype ptr) \
    { \
        type retval; \
        ARCH_ARM_ASM( \
            __ASM_EMIT(cmd "        %[ret], [%[ptr]]") \
            : [ret] "=&r" (retval) \
            : [ptr] "r" (ptr) \
            : "memory" \
        ); \
        return retval; \
    }

namespace lsp
{
    ATOMIC_LOAD_DEF(int8_t, int8_t *, "ldrb")
    ATOMIC_LOAD_DEF(int8_t, const int8_t *, "ldrb")
    ATOMIC_LOAD_DEF(uint8_t, uint8_t *, "ldrb")
    ATOMIC_LOAD_DEF(uint8_t, const uint8_t *, "ldrb")
    ATOMIC_LOAD_DEF(int16_t, int16_t *, "ldrh")
    ATOMIC_LOAD_DEF(int16_t, const int16_t *, "ldrh")
    ATOMIC_LOAD_DEF(uint16_t, uint16_t *, "ldrh")
    ATOMIC_LOAD_DEF(uint16_t, const uint16_t *, "ldrh")
    ATOMIC_LOAD_DEF(int32_t, int32_t *, "ldr")
    ATOMIC_LOAD_DEF(int32_t, const int32_t *, "ldr")
    ATOMIC_LOAD_DEF(uint32_t, uint32_t *, "ldr")
    ATOMIC_LOAD_DEF(uint32_t, const uint32_t *, "ldr")
    ATOMIC_LOAD_DEF(void *, void **, "ldr")
    ATOMIC_LOAD_DEF(void *, void * const *, "ldr")
    ATOMIC_LOAD_DEF(const void *, const void **, "ldr")
    ATOMIC_LOAD_DEF(const void *, const void * const *, "ldr")
} /* namespace lsp */

#undef ATOMIC_LOAD_DEF

#define ATOMIC_STORE_DEF(type, cmd) \
    inline void atomic_store(type *ptr, type value) \
    { \
        ARCH_ARM_ASM( \
            __ASM_EMIT(cmd "        %[value], [%[ptr]]") \
            : \
            : [ptr] "r" (ptr), [value] "r" (value) \
            : "memory" \
        ); \
    }

namespace lsp
{
    ATOMIC_STORE_DEF(int8_t,     "strb")
    ATOMIC_STORE_DEF(uint8_t,    "strb")
    ATOMIC_STORE_DEF(int16_t,    "strh")
    ATOMIC_STORE_DEF(uint16_t,   "strh")
    ATOMIC_STORE_DEF(int32_t,    "str")
    ATOMIC_STORE_DEF(uint32_t,   "str")
    ATOMIC_STORE_DEF(void *,     "str")
} /* namespace lsp */

#undef ATOMIC_STORE_DEF

#define ATOMIC_SWAP_DEF(type, qsz) \
    inline type atomic_swap(type *ptr, type value)      \
    {                                                   \
        type tmp;                                       \
        type retval;                                    \
        \
        ARCH_ARM_ASM                                    \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("ldr" qsz "      %[ret], [%[ptr]]") \
            __ASM_EMIT("str" qsz "      %[tmp], %[src], [%[ptr]]") \
            __ASM_EMIT("tst             %[tmp], %[tmp]") \
            __ASM_EMIT("bne             1b") \
            : [tmp] "=&r" (tmp), \
              [ret] "=&r" (retval)  \
            : [ptr] "r" (ptr), \
              [src] "r" (value) \
            : "memory", "cc"                            \
        );                                              \
        return retval; \
    }

#define ATOMIC_SWAP_DEF2(type) \
    inline type atomic_swap(type *ptr, type value) \
    { \
        while (atomic_swap(&atomic_lock_barrier, uint32_t(1))) /* nothing */ ; \
        type retval = *ptr; \
        *ptr = value; \
        atomic_swap(&atomic_lock_barrier, uint32_t(0)); \
        return retval; \
    }

namespace lsp
{
    ATOMIC_SWAP_DEF(int32_t, "ex")
    ATOMIC_SWAP_DEF(uint32_t, "ex")
    ATOMIC_SWAP_DEF(void *, "ex")
    ATOMIC_SWAP_DEF2(int8_t)
    ATOMIC_SWAP_DEF2(uint8_t)
    ATOMIC_SWAP_DEF2(int16_t)
    ATOMIC_SWAP_DEF2(uint16_t)
} /* namespace lsp */

#undef ATOMIC_SWAP_DEF
#undef ATOMIC_SWAP_DEF2

#define ATOMIC_CAS_DEF(type, qsz)                           \
    inline type atomic_cas(type *ptr, type exp, type rep)   \
    { \
        type tmp; \
        \
        ARCH_ARM_ASM \
        ( \
            __ASM_EMIT("1:") \
            __ASM_EMIT("ldr" qsz "      %[tmp], [%[ptr]]") \
            __ASM_EMIT("cmp             %[tmp], %[exp]") \
            __ASM_EMIT("mov             %[tmp], #0") \
            __ASM_EMIT("bne             2f") \
            __ASM_EMIT("str" qsz "      %[tmp], %[rep], [%[ptr]]") \
            __ASM_EMIT("cmp             %[tmp], #0") \
            __ASM_EMIT("bne             1b") \
            __ASM_EMIT("mov             %[tmp], #1") \
            __ASM_EMIT("2:") \
            : [tmp] "=&r" (tmp) \
            : [ptr] "r" (ptr), [exp] "r" (exp), [rep] "r" (rep) \
            : "cc", "memory" \
        ); \
        return tmp; \
    }

#define ATOMIC_CAS_DEF2(type)                           \
    inline bool atomic_cas(type *ptr, type exp, type rep) \
    { \
        if (!atomic_swap(&atomic_lock_barrier, uint32_t(1))) \
            return false; \
        if (*ptr == exp) \
        { \
            *ptr    = rep; \
            atomic_swap(&atomic_lock_barrier, uint32_t(0)); \
            return true; \
        } \
        \
        atomic_swap(&atomic_lock_barrier, uint32_t(0)); \
        return false; \
    }

namespace lsp
{
    ATOMIC_CAS_DEF(int32_t, "ex")
    ATOMIC_CAS_DEF(uint32_t, "ex")
    ATOMIC_CAS_DEF(void *, "ex")
    ATOMIC_CAS_DEF2(int8_t)
    ATOMIC_CAS_DEF2(uint8_t)
    ATOMIC_CAS_DEF2(int16_t)
    ATOMIC_CAS_DEF2(uint16_t)
} /* namespace lsp */

#undef ATOMIC_CAS_DEF
#undef ATOMIC_CAS_DEF2

#define ATOMIC_ADD_DEF(type, qsz)                       \
    inline type atomic_add(type *ptr, type value)       \
    {                                                   \
        type tmp, sum, retval; \
        \
        ARCH_ARM_ASM                                    \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("ldr" qsz "      %[ret], [%[ptr]]") \
            __ASM_EMIT("add             %[sum], %[ret], %[src]") \
            __ASM_EMIT("str" qsz "      %[tmp], %[sum], [%[ptr]]") \
            __ASM_EMIT("tst             %[tmp], %[tmp]") \
            __ASM_EMIT("bne             1b") \
            : [tmp] "=&r" (tmp), \
              [sum] "=&r" (sum), \
              [ret] "=&r" (retval)  \
            : [ptr] "r" (ptr),  \
              [src] "r" (value) \
            : "memory", "cc"                            \
        );                                              \
        return retval; \
    }

#define ATOMIC_ADD_DEF2(type) \
    inline type atomic_add(type *ptr, type value) \
    {                                                   \
        while (atomic_swap(&atomic_lock_barrier, 1)) /* nothing */ ; \
        type retval = *ptr; \
        *ptr = retval + value; \
        atomic_swap(&atomic_lock_barrier, 0); \
        return retval; \
    }

namespace lsp
{
    ATOMIC_ADD_DEF(int32_t, "ex")
    ATOMIC_ADD_DEF(uint32_t, "ex")
    ATOMIC_ADD_DEF2(int8_t)
    ATOMIC_ADD_DEF2(uint8_t)
    ATOMIC_ADD_DEF2(int16_t)
    ATOMIC_ADD_DEF2(uint16_t)
} /* namespace lsp */

#undef ATOMIC_ADD_DEF
#undef ATOMIC_ADD_DEF2

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
    inline T atomic_trylock(T &lk)
    {
        return T(atomic_cas(
            fixed_int(&lk),
            fixed_int(T(LSP_ATOMIC_UNLOCKED)),
            fixed_int(T(LSP_ATOMIC_LOCKED))
        ));
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



#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_ARMV6_H_ */
