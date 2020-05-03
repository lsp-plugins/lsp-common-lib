/*
 * bits.h
 *
 *  Created on: 1 апр. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_BITS_H_
#define LSP_PLUG_IN_COMMON_BITS_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

// Declare array only for specific architectures
#if (!defined(ARCH_ARM)) && (!defined(ARCH_AARCH64))
namespace lsp
{
    extern const uint8_t    lsp_rb_data[];
}
#endif

// Include CPU-optimized code for bit reversal
#define LSP_PLUG_IN_COMMON_BITS_IMPL
    #if defined(ARCH_X86)
        #include <lsp-plug.in/common/arch/x86/bits.h>
    #elif defined(ARCH_AARCH64)
        #include <lsp-plug.in/common/arch/aarch64/bits.h>
    #elif defined(ARCH_ARM)
        #include <lsp-plug.in/common/arch/arm/bits.h>
    #else
        #include <lsp-plug.in/common/arch/native/bits.h>
    #endif
#undef LSP_PLUG_IN_COMMON_BITS_IMPL


#endif /* LSP_PLUG_IN_COMMON_BITS_H_ */
