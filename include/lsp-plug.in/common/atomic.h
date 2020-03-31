/*
 * atomic.h
 *
 *  Created on: 31 мар. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_ATOMIC_H_
#define LSP_PLUG_IN_COMMON_ATOMIC_H_

#include <lsp-plug.in/common/types.h>

/**
  Common atomic interface:

    Atomically swap the value 'value' with memory chunk pointed by
    'ptr' and return the previous value stored in memory chunk as 'ret':

        ret atomic_swap(*ptr, value)

    Atomicatlly add value 'value' to memory chunk pointed by 'ptr'
    and return the previous value stored in memory chunk as 'ret':

        ret atomic_add(*ptr, value)

    Atomically compare contents of memory chunk pointed by 'ptr'
    with expected value 'exp' and overwrite it with replacement 'rep'
    if they match. Return true on success, fail on error as 'ret'.

        ret atomic_cas(*ptr, exp, rep)
*/
namespace lsp
{
    typedef unsigned int    uatomic_t;
    typedef signed int      atomic_t;
}

#define LSP_PLUG_IN_COMMON_ATOMIC_IMPL
    #if defined(ARCH_X86) /* x86 and x86_64 implementation */
        #include <lsp-plug.in/common/arch/x86/atomic.h>
    #elif defined(ARCH_AARCH64) /* ARM 64-bit implementation */
        #include <lsp-plug.in/common/arch/aarch64/atomic.h>
    #elif defined(ARCH_ARM) /* ARM 32-bit implementation */
        #include <lsp-plug.in/common/arch/arm/atomic.h>
    #else /* Generic implementation */
        #include <lsp-plug.in/common/arch/generic/atomic.h>
    #endif /* ARCH_X86 */
#undef LSP_PLUG_IN_COMMON_ATOMIC_IMPL

#endif /* INCLUDE_LSP_PLUG_IN_COMMON_ATOMIC_H_ */
