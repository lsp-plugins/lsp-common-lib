/*
 * atomic.h
 *
 *  Created on: 31 мар. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_
#define LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_ATOMIC_IMPL */


#define ATOMIC_CAS_DEF(type, qsz, M, extra)                     \
    inline type atomic_cas(extra type *ptr, type exp, type rep) \
    { \
        type tmp; \
        uint32_t res; \
        \
        ARCH_AARCH64_ASM \
        ( \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" M "[tmp], [%[ptr]]") \
            __ASM_EMIT("subs            %" M "[tmp], %" M "[tmp], %" M "[exp]")    /* tmp == 0 on success */ \
            __ASM_EMIT("b.ne            2f")                                       /* jump if failed */ \
            __ASM_EMIT("stxr" qsz "     %w[res], %" M "[rep], [%[ptr]]")            /* try to store replacement */ \
            __ASM_EMIT("tst             %w[res], %w[res]")                          /* ret == 0 on success */ \
            __ASM_EMIT("2:") \
            __ASM_EMIT("cset            %[tmp], eq") \
            : [tmp] "=&r" (tmp), [res] "=&r" (res) \
            : [ptr] "r" (ptr), [exp] "r" (exp), [rep] "r" (rep) \
            : "cc", "memory" \
        ); \
        return tmp; \
    }

namespace lsp
{
    ATOMIC_CAS_DEF(int8_t, "b", "", )
    ATOMIC_CAS_DEF(int8_t, "b", "", volatile)
    ATOMIC_CAS_DEF(uint8_t, "b", "", )
    ATOMIC_CAS_DEF(uint8_t, "b", "", volatile)
    ATOMIC_CAS_DEF(int16_t, "h", "", )
    ATOMIC_CAS_DEF(int16_t, "h", "", volatile)
    ATOMIC_CAS_DEF(uint16_t, "h", "", )
    ATOMIC_CAS_DEF(uint16_t, "h", "", volatile)
    ATOMIC_CAS_DEF(int32_t, "", "w", )
    ATOMIC_CAS_DEF(int32_t, "", "w", volatile)
    ATOMIC_CAS_DEF(uint32_t, "", "w", )
    ATOMIC_CAS_DEF(uint32_t, "", "w", volatile)
    ATOMIC_CAS_DEF(int64_t, "", "", )
    ATOMIC_CAS_DEF(int64_t, "", "", volatile)
    ATOMIC_CAS_DEF(uint64_t, "", "", )
    ATOMIC_CAS_DEF(uint64_t, "", "", volatile)
}

#undef ATOMIC_CAS_DEF

#define ATOMIC_ADD_DEF(type, qsz, M, extra) \
    inline type atomic_add(extra type *ptr, type value) \
    {                                                   \
        uint32_t tmp; \
        type sum, retval; \
        \
        ARCH_AARCH64_ASM                                \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" M "[ret], [%[ptr]]") \
            __ASM_EMIT("add             %" M "[sum], %" M "[ret], %" M "[src]") \
            __ASM_EMIT("stxr" qsz "     %w[tmp], %" M "[sum], [%[ptr]]") \
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
    ATOMIC_ADD_DEF(int8_t, "b", "", )
    ATOMIC_ADD_DEF(int8_t, "b", "", volatile)
    ATOMIC_ADD_DEF(uint8_t, "b", "", )
    ATOMIC_ADD_DEF(uint8_t, "b", "", volatile)
    ATOMIC_ADD_DEF(int16_t, "h", "", )
    ATOMIC_ADD_DEF(int16_t, "h", "", volatile)
    ATOMIC_ADD_DEF(uint16_t, "h", "", )
    ATOMIC_ADD_DEF(uint16_t, "h", "", volatile)
    ATOMIC_ADD_DEF(int32_t, "", "w", )
    ATOMIC_ADD_DEF(int32_t, "", "w", volatile)
    ATOMIC_ADD_DEF(uint32_t, "", "w", )
    ATOMIC_ADD_DEF(uint32_t, "", "w", volatile)
    ATOMIC_ADD_DEF(int64_t, "", "", )
    ATOMIC_ADD_DEF(int64_t, "", "", volatile)
    ATOMIC_ADD_DEF(uint64_t, "", "", )
    ATOMIC_ADD_DEF(uint64_t, "", "", volatile)
}

#undef ATOMIC_ADD_DEF

#define ATOMIC_SWAP_DEF(type, qsz, M, extra) \
    inline type atomic_swap(extra type *ptr, type value) \
    {                                                   \
        uint32_t tmp; \
        type retval; \
        \
        ARCH_AARCH64_ASM                                \
        (                                               \
            __ASM_EMIT("1:")    \
            __ASM_EMIT("dmb st") \
            __ASM_EMIT("ldaxr" qsz "    %" M "[ret], [%[ptr]]") \
            __ASM_EMIT("stxr" qsz "     %w[tmp], %" M "[value], [%[ptr]]") \
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
    ATOMIC_SWAP_DEF(int8_t, "b", "", )
    ATOMIC_SWAP_DEF(int8_t, "b", "", volatile)
    ATOMIC_SWAP_DEF(uint8_t, "b", "", )
    ATOMIC_SWAP_DEF(uint8_t, "b", "", volatile)
    ATOMIC_SWAP_DEF(int16_t, "h", "", )
    ATOMIC_SWAP_DEF(int16_t, "h", "", volatile)
    ATOMIC_SWAP_DEF(uint16_t, "h", "", )
    ATOMIC_SWAP_DEF(uint16_t, "h", "", volatile)
    ATOMIC_SWAP_DEF(int32_t, "", "w", )
    ATOMIC_SWAP_DEF(int32_t, "", "w", volatile)
    ATOMIC_SWAP_DEF(uint32_t, "", "w", )
    ATOMIC_SWAP_DEF(uint32_t, "", "w", volatile)
    ATOMIC_SWAP_DEF(int64_t, "", "", )
    ATOMIC_SWAP_DEF(int64_t, "", "", volatile)
    ATOMIC_SWAP_DEF(uint64_t, "", "", )
    ATOMIC_SWAP_DEF(uint64_t, "", "", volatile)
}

#undef ATOMIC_SWAP_DEF

//-----------------------------------------------------------------------------
// Atomic operations
namespace lsp
{
    template <class type_t>
        inline void atomic_init(type_t &lk) { lk = 1; }

    template <class type_t>
        inline type_t atomic_trylock(type_t &lk) { return atomic_cas(&lk, 1, 0); }

    template <class type_t>
        inline type_t atomic_unlock(type_t &lk) { return atomic_swap(&lk, 1); }
}


#endif /* LSP_PLUG_IN_COMMON_ARCH_AARCH64_ATOMIC_H_ */
