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

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_LEGACY_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_LEGACY_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */

namespace lsp
{
    extern uint32_t atomic_lock_barrier;
} /* namespace lsp */

#define ATOMIC_LOAD_DEF(type, cmd) \
    inline type atomic_load(type *ptr) \
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
    ATOMIC_LOAD_DEF(int8_t,     "ldrb")
    ATOMIC_LOAD_DEF(uint8_t,    "ldrb")
    ATOMIC_LOAD_DEF(int16_t,    "ldrh")
    ATOMIC_LOAD_DEF(uint16_t,   "ldrh")
    ATOMIC_LOAD_DEF(int32_t,    "ldr")
    ATOMIC_LOAD_DEF(uint32_t,   "ldr")
    ATOMIC_LOAD_DEF(void *,     "ldr")
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

#define ATOMIC_SWAP_DEF(type, cmd) \
    inline type atomic_swap(type *ptr, type value) \
    { \
        type retval; \
        ARCH_ARM_ASM( \
            __ASM_EMIT(cmd "        %[ret], %[src], [%[ptr]]") \
            : [ret] "=&r" (retval) \
            : [ptr] "r" (ptr), \
              [src] "r" (value) \
            : "memory" \
        ); \
        return retval; \
    }

#define ATOMIC_SWAP_DEF2(type) \
    inline type atomic_swap(type *ptr, type value) \
    { \
        while (atomic_swap(&atomic_lock_barrier, 1)) /* nothing */ ; \
        type retval = *ptr; \
        *ptr = value; \
        atomic_swap(&atomic_lock_barrier, 0); \
        return retval; \
    }

#define ATOMIC_SWAP_DEF3(type) \
    inline type atomic_swap(type *ptr, type value) \
    { \
        while (atomic_swap(&atomic_lock_barrier, 1)) /* nothing */ ; \
        type retval = *ptr; \
        *ptr = value; \
        atomic_swap(&atomic_lock_barrier, 0); \
        return retval; \
    }

namespace lsp
{
    ATOMIC_SWAP_DEF(int8_t,     "swpb")
    ATOMIC_SWAP_DEF(uint8_t,    "swpb")
    ATOMIC_SWAP_DEF(int32_t,    "swp")
    ATOMIC_SWAP_DEF(uint32_t,   "swp")

    ATOMIC_SWAP_DEF2(int16_t)
    ATOMIC_SWAP_DEF2(uint16_t)
    ATOMIC_SWAP_DEF3(void *)
} /* namespace lsp */

#undef ATOMIC_SWAP_DEF
#undef ATOMIC_SWAP_DEF2
#undef ATOMIC_SWAP_DEF3


#define ATOMIC_CAS_DEF(type)                        \
    inline bool atomic_cas(type *ptr, type exp, type rep) \
    { \
        if (!atomic_swap(&atomic_lock_barrier, 1)) \
            return false; \
        if (*ptr == exp) \
        { \
            *ptr    = rep; \
            atomic_swap(&atomic_lock_barrier, 0); \
            return true; \
        } \
        \
        atomic_swap(&atomic_lock_barrier, 0); \
        return false; \
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
} /* namespace lsp */

#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type) \
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
    ATOMIC_ADD_DEF(int8_t)
    ATOMIC_ADD_DEF(uint8_t)
    ATOMIC_ADD_DEF(int16_t)
    ATOMIC_ADD_DEF(uint16_t)
    ATOMIC_ADD_DEF(int32_t)
    ATOMIC_ADD_DEF(uint32_t)
} /* namespace lsp */

#undef ATOMIC_ADD_DEF

//-----------------------------------------------------------------------------
// Atomic operations

#define LSP_ATOMIC_UNLOCKED     1
#define LSP_ATOMIC_LOCKED       0

namespace lsp
{
    template <class type_t>
        inline void atomic_init(type_t &lk) { lk = LSP_ATOMIC_UNLOCKED; }

    template <class type_t>
        inline type_t atomic_trylock(type_t &lk) { return atomic_swap(&lk, LSP_ATOMIC_LOCKED); }

    template <class type_t>
        inline type_t atomic_unlock(type_t &lk) { return atomic_swap(&lk, LSP_ATOMIC_UNLOCKED); }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_ATOMIC_LEGACY_H_ */
