/*
 * Copyright (C) 2024 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2024 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 10 авг. 2018 г.
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

#ifndef LSP_PLUG_IN_COMMON_TYPES_H_
#define LSP_PLUG_IN_COMMON_TYPES_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/finally.h>

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>

//-----------------------------------------------------------------------------
// VERSION MANAGEMENT
#define LSP_DEF_VERSION(major, minor, micro)        { major, minor, micro, ""       }
#define LSP_DEF_PACKAGE(major, minor, micro, branch){ major, minor, micro, branch   }
#define LSP_DEFINE_VERSION(artifact)                LSP_DEF_VERSION(artifact##_MAJOR, artifact##_MINOR, artifact##_MICRO)

#define LSP_DO_DEFINE_VERSION_STR(major, minor, micro) #major "." #minor "." #micro
#define LSP_DEF_VERSION_STR(major, minor, micro)    LSP_DO_DEFINE_VERSION_STR(major, minor, micro)
#define LSP_DEFINE_VERSION_STR(artifact)            LSP_DEF_VERSION_STR(artifact##_MAJOR, artifact##_MINOR, artifact##_MICRO)

#define LSP_VERSION_FUNC_NAME                       "lsp_module_version"

#define LSP_DEF_VERSION_FUNC_HEADER                 const ::lsp::version_t *lsp_module_version()
#define LSP_DEF_VERSION_FUNC(major, minor, micro)   \
    LSP_DEF_VERSION_FUNC_HEADER \
    { \
        static const ::lsp::version_t v=LSP_DEF_VERSION(major, minor, micro); \
        return &v; \
    }

#define LSP_DEFINE_VERSION_FUNC(artifact)           LSP_DEF_VERSION_FUNC(artifact##_MAJOR, artifact##_MINOR, artifact##_MICRO)

#define LSP_STRINGIFY(x)                            LSP_STRINGIFY1(x)
#define LSP_STRINGIFY1(x)                           #x

//-----------------------------------------------------------------------------
// Detect build architecture
#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64) || defined(_M_AMD64)
    #define ARCH_X86
    #define ARCH_X86_64
#elif defined(__i386__) || defined(__i386)
    #define ARCH_X86
    #define ARCH_I386
#elif defined(__aarch64__)
    #define ARCH_AARCH64
#elif defined(__arm__) || defined(__arm) || defined(_M_ARM) || defined(_ARM)
    #define ARCH_ARM
#elif defined(__PPC64__) || defined(__ppc64__) || defined(__ppc64) || defined(__powerpc64__) || defined(_ARCH_PPC64)
    #define ARCH_PPC64
#elif defined(__PPC__) || defined(__ppc__) || defined(__powerpc__) || defined(__ppc) || defined(_M_PPC) || defined(_ARCH_PPC)
    #define ARCH_PPC
#elif defined(__s390x__) || defined(__s390__) || defined(__zarch__)
    #define ARCH_S390
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__)
    #define ARCH_MIPS
#elif defined(__sparc__) || defined(__sparc)
    #define ARCH_SPARC
#elif defined(__riscv) && (__riscv_xlen == 64)
    #define ARCH_RISCV
    #define ARCH_RISCV64
#elif defined(__riscv) && (__riscv_xlen == 32)
    #define ARCH_RISCV
    #define ARCH_RISCV32
#elif defined(__loongarch64)
    #define ARCH_LOONGARCH
    #define ARCH_LOONGARCH64
#elif defined(__loongarch32)
    #define ARCH_LOONGARCH
    #define ARCH_LOONGARCH32
#endif

//-----------------------------------------------------------------------------
// Detect endianess of architecture
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    #define ARCH_LE
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define ARCH_BE
#endif

//-----------------------------------------------------------------------------
// Detect bitness of architecture
namespace lsp
{
    #if defined(__WORDSIZE) && (__WORDSIZE == 128)
        #define ARCH_128BIT
    #elif defined(__SIZE_WIDTH__) && (__SIZE_WIDTH__ == 128)
        #define ARCH_128BIT
    #elif defined(__WORDSIZE) && (__WORDSIZE == 64)
        #define ARCH_64BIT
    #elif defined(__SIZE_WIDTH__) && (__SIZE_WIDTH__ == 64)
        #define ARCH_64BIT
    #elif defined(__WORDSIZE) && (__WORDSIZE == 32)
        #define ARCH_32BIT
    #elif defined(__SIZE_WIDTH__) && (__SIZE_WIDTH__ == 32)
        #define ARCH_32BIT
    #else
        #warning "Unsupported architecture bitness"
    #endif /* __WORDSIZE, __SIZE_WIDTH__ */

    #if defined(ARCH_32BIT)
        #ifndef INT32_MIN
            #define INT32_MIN           (-2147483647-1)
        #endif

        #ifndef INT32_MAX
            #define INT32_MAX           (2147483647)
        #endif

        #ifndef UINT32_MAX
            #define UINT32_MAX          (4294967295U)
        #endif

        #define UMWORD_MIN          0
        #define UMWORD_MAX          UINT32_MAX
        #define UMWORD_BITS         32

        #define SMWORD_MIN          INT32_MIN
        #define SMWORD_MAX          INT32_MAX
        #define SMWORD_BITS         32

        typedef uint32_t            umword_t;
        typedef int32_t             smword_t;
    #elif defined(ARCH_64BIT)
        #ifndef INT64_MIN
            #define INT64_MIN           (-9223372036854775807L-1)
        #endif

        #ifndef INT64_MAX
            #define INT64_MAX           (9223372036854775807L)
        #endif

        #ifndef UINT64_MAX
            #define UINT64_MAX          (18446744073709551615UL)
        #endif

        #define UMWORD_MIN          0
        #define UMWORD_MAX          UINT64_MAX
        #define UMWORD_BITS         64

        #define SMWORD_MIN          INT64_MIN
        #define SMWORD_MAX          INT64_MAX
        #define SMWORD_BITS         64

        typedef uint64_t            umword_t;
        typedef int64_t             smword_t;
    #elif defined(ARCH_128BIT)
        #define UMWORD_MIN          0
        #define UMWORD_MAX          UINT128_MAX
        #define UMWORD_BITS         128

        #define SMWORD_MIN          INT128_MIN
        #define SMWORD_MAX          INT128_MAX
        #define SMWORD_BITS         128

        typedef uint128_t           umword_t;
        typedef int128_t            smword_t;
    #endif

    /**
     * Version of any plugin module
     */
    typedef struct version_t
    {
        int         major;      /* Major version */
        int         minor;      /* Minor version */
        int         micro;      /* Micro version */
        const char *branch;     /* Branch version */
    } version_t;

    /**
     * Function that returns module version
     * @return version structure
     */
    typedef const version_t *(* module_version_t)();

    /**
     * Definition of nullptr_t
     */
    typedef decltype(nullptr)   nullptr_t;
}

//-----------------------------------------------------------------------------
// Detect endianess and operations
#if defined(ARCH_X86) || defined(ARCH_X86_64)
    #define IF_ARCH_X86(...)        __VA_ARGS__
    #define ARCH_X86_ASM(...)       __asm__ __volatile__ ( __VA_ARGS__ )
    #define LSP_UNALIGNED_MEMORY_SAFE
#endif /* ARCH_X86 */

#if defined(ARCH_I386)
    #define IF_ARCH_I386(...)       __VA_ARGS__
    #define ARCH_I386_ASM(...)      __asm__ __volatile__ ( __VA_ARGS__ )
    #define ARCH_STRING             "i386"
#endif /* ARCH_I386 */

#if defined(ARCH_X86_64)
    #define IF_ARCH_X86_64(...)     __VA_ARGS__
    #define ARCH_X86_64_ASM(...)    __asm__ __volatile__ ( __VA_ARGS__ )
    #define ARCH_STRING             "x86_64"
#endif /* defined(ARCH_X86_64) */

#if defined(ARCH_ARM)
    #define IF_ARCH_ARM(...)            __VA_ARGS__
    #define ARCH_ARM_ASM(...)           __asm__ __volatile__ ( __VA_ARGS__ )

    #if !defined(ARCH_BE) && !defined(ARCH_BE)
        #define ARCH_LE
    #endif

    #if (__ARM_ARCH >= 7)
        #define ARCH_ARM7
        #define ARCH_STRING             "armv7a"
        #define IF_ARCH_ARM7(...)        __VA_ARGS__
        #define IF_ARCH_LEAST_ARM7(...)  __VA_ARGS__
    #elif (__ARM_ARCH == 6)
        #define ARCH_ARM6
        #define ARCH_STRING             "armv6a"
        #define IF_ARCH_ARM6(...)        __VA_ARGS__
        #define IF_ARCH_LEAST_ARM6(...)  __VA_ARGS__
    #else
        #define ARCH_STRING             "arm-generic"
    #endif
#endif /* defined(ARCH_ARM) */

#if defined(ARCH_AARCH64)
    #define IF_ARCH_AARCH64(...)        __VA_ARGS__
    #define ARCH_AARCH64_ASM(...)       __asm__ __volatile__ ( __VA_ARGS__ )

    #if !defined(ARCH_BE) && !defined(ARCH_BE)
        #define ARCH_LE
    #endif

    #define ARCH_STRING                 "aarch64"

    #if (__ARM_ARCH >= 8)
        #define ARCH_ARM8
        #define IF_ARCH_ARM8(...)        __VA_ARGS__
    #endif
#endif /* defined(ARCH_ARM) */

#if defined(ARCH_PPC)
    #define IF_ARCH_PPC(...)            __VA_ARGS__
    #define ARCH_PPC_ASM(...)           __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "ppc"
#endif /* defined(ARCH_PPC) */

#if defined(ARCH_PPC64)
    #define IF_ARCH_PPC64(...)          __VA_ARGS__
    #define ARCH_PPC64_ASM(...)         __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "ppc64"
#endif /* defined(ARCH_PPC) */

#if defined(ARCH_S390)
    #define IF_ARCH_S390(...)           __VA_ARGS__
    #define ARCH_S390_ASM(...)          __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "S390"
#endif /* defined(ARCH_PPC) */

#if defined(ARCH_MIPS)
    #define IF_ARCH_MIPS(...)           __VA_ARGS__
    #define ARCH_MIPS_ASM(...)          __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "MIPS"
#endif /* defined(ARCH_PPC) */

#if defined(ARCH_SPARC)
    #define IF_ARCH_SPARC(...)          __VA_ARGS__
    #define ARCH_SPARC_ASM(...)         __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "SPARC"
#endif /* defined(ARCH_PPC) */

#if defined(ARCH_RISCV)
    #define IF_ARCH_RISCV(...)          __VA_ARGS__
    #define ARCH_RISCV_ASM(...)         __asm__ __volatile__ ( __VA_ARGS__ )
#endif /* ARCH_RISCV */

#if defined(ARCH_RISCV64)
    #define IF_ARCH_RISCV64(...)        __VA_ARGS__
    #define ARCH_RISCV64_ASM(...)       __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "RISCV64"
#endif /* defined(ARCH_RISCV64) */

#if defined(ARCH_RISCV32)
    #define IF_ARCH_RISCV32(...)        __VA_ARGS__
    #define ARCH_RISCV32_ASM(...)       __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "RISCV32"
#endif /* defined(ARCH_RISCV32) */

#if defined(ARCH_LOONGARCH)
    #define IF_ARCH_LOONGARCH(...)      __VA_ARGS__
    #define ARCH_LOONGARCH_ASM(...)     __asm__ __volatile__ ( __VA_ARGS__ )
#endif /* ARCH_LOONGARCH */

#if defined(ARCH_LOONGARCH64)
    #define IF_ARCH_LOONGARCH64(...)    __VA_ARGS__
    #define ARCH_LOONGARCH64_ASM(...)   __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "LOONGARCH64"
#endif /* defined(ARCH_LOONGARCH64) */

#if defined(ARCH_LOONGARCH32)
    #define IF_ARCH_LOONGARCH32(...)    __VA_ARGS__
    #define ARCH_LOONGARCH32_ASM(...)   __asm__ __volatile__ ( __VA_ARGS__ )

    #define ARCH_STRING                 "LOONGARCH32"
#endif /* defined(ARCH_LOONGARCH32) */

#if defined(ARCH_LE)
    #define __IF_LEBE(le, be)   le
    #define __IF_LE(le)         le
    #define __IF_BE(be)
    #ifdef ARCH_BE
        #undef ARCH_BE
    #endif /* ARCH_BE */
#elif defined(ARCH_BE) /* ARCH_BE */
    #define __IF_LEBE(le, be)   be
    #define __IF_LE(le)
    #define __IF_BE(be)         be

    #ifdef ARCH_LE
        #undef ARCH_LE
    #endif /* ARCH_LE */
#else
    #warning "Could not detect endianess of the target architecture"
#endif /* ARCH_LE */

#ifndef ARCH_STRING
    #define ARCH_STRING                 "native"
#endif /* ARCH_STRING */

//-----------------------------------------------------------------------------
// Detect build platform
#if defined(__unix__) || defined(unix) || defined(__unix)
    #define PLATFORM_UNIX
    #define IF_PLATFORM_UNIX(...)       __VA_ARGS__
#endif /* __unix__ */

#if defined(__sun__) || defined(__sun) || defined(sun)
    #define PLATFORM_SOLARIS
    #define IF_PLATFORM_SOLARIS(...)    __VA_ARGS__
#endif /* __sun__ */

#if defined(__linux__) || defined(__linux) || defined(linux)
    #define PLATFORM_LINUX
    #define IF_PLATFORM_LINUX(...)      __VA_ARGS__
#endif /* __linux__ */

#if defined(__FreeBSD__)
    #define PLATFORM_FREEBSD
    #define IF_PLATFORM_FREEBSD(...)    __VA_ARGS__
#endif /* __FreeBSD__ */

#if defined(__OpenBSD__)
    #define PLATFORM_OPENBSD
    #define IF_PLATFORM_OPENBSD(...)    __VA_ARGS__
#endif /* __FreeBSD__ */

#if defined(__bsd__) || defined(__bsd) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(freebsd) || defined(openbsd) || defined(bsdi) || defined(__darwin__)
    #define PLATFORM_BSD
    #define IF_PLATFORM_BSD(...)        __VA_ARGS__
#endif /* __bsd__ */

#if defined(__macosx__) || defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__)
    #define PLATFORM_MACOSX
    #define IF_PLATFORM_MACOSX(...)     __VA_ARGS__
#endif /* __macosx__ */

#if defined(__WINDOWS__) || defined(__WIN32__) || defined(__WIN64__) || defined(_WIN64) || defined(_WIN32) || defined(__WINNT) || defined(__WINNT__)
    #define PLATFORM_WINDOWS
    #define IF_PLATFORM_WINDOWS(...)    __VA_ARGS__
#endif /* __macosx__ */

#if defined(__HAIKU__)
    #define PLATFORM_HAIKU
    #define IF_PLATFORM_HAIKU(...)      __VA_ARGS__
#endif /* __Haiku__ */

#if defined(PLATFORM_UNIX) || defined(PLATFORM_LINUX) || defined(PLATFORM_MACOSX) || defined(PLATFORM_BSD) || defined(PLATFORM_HAIKU)
    #define PLATFORM_UNIX_COMPATIBLE
    #define PLATFORM_POSIX

    #define IF_PLATFORM_POSIX(...)      __VA_ARGS__
#endif /* unix-compatible platforms */

// File separators for platform tuning
#if defined(PLATFORM_UNIX_COMPATIBLE)
    #define FILE_SEPARATOR_C            '/'
    #define FILE_SEPARATOR_S            "/"
    #define FILE_SYSTEM_CASE_SENSE      1
    #define FILE_LIBRARY_EXT_S          ".so"
#elif defined(PLATFORM_WINDOWS)
    #define FILE_SEPARATOR_C            '\\'
    #define FILE_SEPARATOR_S            "\\"
    #define FILE_SYSTEM_CASE_SENSE      0
    #define FILE_LIBRARY_EXT_S          ".dll"
#endif /* */

// Detect compiler
#if defined(__clang__)
    #define COMPILER_CLANG
    #define __IF_CLANG(...)             __VA_ARGS__
    #define __IFN_CLANG(...)
#elif defined(__GNUC__) || defined(__GNUG__)
    #define COMPILER_GCC
    #define __IF_GCC(...)               __VA_ARGS__
    #define __IFN_GCC(...)
#elif defined(_MSC_VER)
    #define COMPILER_MSC
    #define __IF_MSC(...)               __VA_ARGS__
    #define __IFN_MSC(...)
#endif /* __GNUC__ */

#ifndef __IF_CLANG
    #define __IF_CLANG(...)
#endif /*__IF_CLANG */

#ifndef __IFN_CLANG
    #define __IFN_CLANG(...)            __VA_ARGS__
#endif /*__IFN_CLANG */

#ifndef __IF_GCC
    #define __IF_GCC(...)
#endif /*__IF_GCC */

#ifndef __IFN_GCC
    #define __IFN_GCC(...)              __VA_ARGS__
#endif /*__IFN_GCC */

#ifndef __IF_MSC
    #define __IF_MSC(...)
#endif /*__IF_MSC */

#ifndef __IFN_MSC
    #define __IFN_MSC(...)              __VA_ARGS__
#endif /*__IFN_MSC */

//-----------------------------------------------------------------------------
// Conditional assemblying
#define __ASM_EMIT(code)                        code "\n\t"

#ifdef ARCH_32BIT
    #define __ASM_EMIT32(code)                  code "\n\t"
    #define __IF_32(...)                        __VA_ARGS__
    #define __IF_32_64(a, b)                    a

    #ifdef LSP_PROFILING
        #define __IF_32P(...)                       __VA_ARGS__
        #define __ASM_EMIT32P(code)                 code "\n\t"
    #else
        #define __IF_32NP(...)                      __VA_ARGS__
        #define __ASM_EMIT32NP(code)                code "\n\t"
    #endif /* LSP_PROFILING */
#endif /* ARCH_32BIT */

#ifdef ARCH_64BIT
    #define __ASM_EMIT64(code)                  code "\n\t"
    #define __IF_64(...)                        __VA_ARGS__
    #define __IF_32_64(a, b)                    b
    #ifdef LSP_PROFILING
        #define __IF_64P(...)                       __VA_ARGS__
        #define __ASM_EMIT64P(code)                 code "\n\t"
    #else
        #define __IF_64NP(...)                      __VA_ARGS__
        #define __ASM_EMIT64NP(code)                code "\n\t"
    #endif /* LSP_PROFILING */
#endif /* ARCH_32BIT */

#ifdef LSP_PROFILING
    #define __ASM_EMITP(code)                      code "\n\t"
    #define __ASM_EMITNP(code)
#else
    #define __ASM_EMITP(code)
    #define __ASM_EMITNP(code)                     code "\n\t"
#endif /* LSP_PROFILING */

#ifndef ARCH_X86_ASM
    #define ARCH_X86_ASM(...)
#endif /* ARCH_X86_ASM */

#ifndef ARCH_I386_ASM
    #define ARCH_I386_ASM(...)
#endif /* ARCH_I386_ASM */

#ifndef ARCH_X86_64_ASM
    #define ARCH_X86_64_ASM(...)
#endif /* ARCH_I386_ASM */

#ifndef ARCH_ARM_ASM
    #define ARCH_ARM_ASM(...)
#endif /* ARCH_ARM_ASM */

#ifndef ARCH_AARCH64_ASM
    #define ARCH_AARCH64_ASM(...)
#endif /* ARCH_AARCH64_ASM */

#ifndef ARCH_PPC64_ASM
    #define ARCH_PPC64_ASM(...)
#endif /* ARCH_PPC64_ASM */

#ifndef ARCH_PPC_ASM
    #define ARCH_PPC_ASM(...)
#endif /* ARCH_PPC_ASM */

#ifndef ARCH_S390_ASM
    #define ARCH_S390_ASM(...)
#endif /* ARCH_S390_ASM */

#ifndef ARCH_MIPS_ASM
    #define ARCH_MIPS_ASM(...)
#endif /* ARCH_MIPS_ASM */

#ifndef ARCH_SPARC_ASM
    #define ARCH_SPARC_ASM(...)
#endif /* ARCH_SPARC_ASM */

#define __ASM_ARG_TMP(var)                      __IF_32P("=&g"(var)) __IF_32NP("=&r"(var)) __IF_64("=&r"(var))
#define __ASM_ARG_RW(var)                       __IF_32P("+g"(var))  __IF_32NP("+r"(var))  __IF_64("+r"(var))
#define __ASM_ARG_RO(var)                       __IF_32P("g"(var))   __IF_32NP("r"(var))   __IF_64("r"(var))

#define __lsp_forced_inline                 __attribute__ ((always_inline))
#define __lsp_aligned16                     __attribute__ ((aligned (16)))
#define __lsp_aligned32                     __attribute__ ((aligned (32)))
#define __lsp_aligned64                     __attribute__ ((aligned (64)))
#define __lsp_packed                        __attribute__ ((__packed__))
#define __lsp_aligned(bytes)                __attribute__ ((aligned (bytes)))

//-----------------------------------------------------------------------------
// CPU extensions

// Extensions for x86 architecture enabled by compiler
#ifdef ARCH_X86
    #ifdef __SSE__
        #define ARCH_X86_SSE
    #endif /* __SSE__ */

    #ifdef __SSE2__
        #define ARCH_X86_SSE2
    #endif /* __SSE2__ */

    #ifdef __SSE3__
        #define ARCH_X86_SSE3
    #endif /* __SSE2__ */

    #ifdef __SSSE3__
        #define ARCH_X86_SSSE3
    #endif /* __SSE2__ */

    #ifdef __SSE4_1__
        #define ARCH_X86_SSE4_1
    #endif /* __SSE4_1__ */

    #ifdef __SSE4_2__
        #define ARCH_X86_SSE4_2
    #endif /* __SSE4_1__ */

    #ifndef LSP_NO_AVX /* Special directive that forces to disable AVX support */
        #ifdef __AVX__
            #define ARCH_X86_AVX
            #ifdef ARCH_X86_64
                #define ARCH_X86_64_AVX
            #else
                #define ARCH_I386_AVX
            #endif
        #endif /* __AVX__ */

        #ifdef __AVX2__
            #define ARCH_X86_AVX2
            #ifdef ARCH_X86_64
                #define ARCH_X86_64_AVX2
            #else
                #define ARCH_I386_AVX2
            #endif
        #endif /* __AVX2__ */
    #endif /* LSP_NO_AVX */
#endif /* ARCH_X86 */


//-----------------------------------------------------------------------------
// Define macros that may not be previously defined
#ifndef __ASM_EMIT32
    #define __ASM_EMIT32(code)
#endif /* __ASM_EMIT32 */

#ifndef __ASM_EMIT32P
    #define __ASM_EMIT32P(code)
#endif /* __ASM_EMIT32P */

#ifndef __ASM_EMIT32NP
    #define __ASM_EMIT32NP(code)
#endif /* __ASM_EMIT32NP */

#ifndef __ASM_EMIT64
    #define __ASM_EMIT64(code)
#endif /* __ASM_EMIT64 */

#ifndef __ASM_EMIT64P
    #define __ASM_EMIT64P(code)
#endif /* __ASM_EMIT64P */

#ifndef __ASM_EMIT64NP
    #define __ASM_EMIT64NP(code)
#endif /* __ASM_EMIT64NP */

#ifndef __IF_32
    #define __IF_32(...)
#endif /* __IF_32 */

#ifndef __IF_32P
    #define __IF_32P(...)
#endif /* __IF_32 */

#ifndef __IF_32NP
    #define __IF_32NP(...)
#endif /* __IF_32 */

#ifndef __IF_64
    #define __IF_64(...)
#endif /* __IF_64 */

//-----------------------------------------------------------------------------
// Default architectures
#ifndef IF_ARCH_X86
    #define IF_ARCH_X86(...)
#endif /* IF_ARCH_X86 */

#ifndef IF_ARCH_I386
    #define IF_ARCH_I386(...)
#endif /* IF_ARCH_I386 */

#ifndef IF_ARCH_X86_64
    #define IF_ARCH_X86_64(...)
#endif /* IF_ARCH_X86_64 */

#ifndef IF_ARCH_ARM
    #define IF_ARCH_ARM(...)
#endif /* IF_ARCH_ARM */

#ifndef IF_ARCH_ARM6
    #define IF_ARCH_ARM6(...)
#endif /* IF_ARCH_ARM6 */

#ifndef IF_ARCH_LEAST_ARM6
    #define IF_ARCH_LEAST_ARM6(...)
#endif /* IF_ARCH_LEAST_ARM6 */

#ifndef IF_ARCH_ARM7
    #define IF_ARCH_ARM7(...)
#endif /* IF_ARCH_ARM7 */

#ifndef IF_ARCH_LEAST_ARM7
    #define IF_ARCH_LEAST_ARM7(...)
#endif /* IF_ARCH_LEAST_ARM7 */

#ifndef IF_ARCH_ARM8
    #define IF_ARCH_ARM8(...)
#endif /* IF_ARCH_ARM8 */

#ifndef IF_ARCH_AARCH64
    #define IF_ARCH_AARCH64(...)
#endif /* IF_ARCH_AARCH64 */

#ifndef IF_ARCH_PPC
    #define IF_ARCH_PPC(...)
#endif /* IF_ARCH_PPC */

#ifndef IF_ARCH_PPC64
    #define IF_ARCH_PPC64(...)
#endif /* IF_ARCH_PPC64 */

#ifndef IF_ARCH_S390
    #define IF_ARCH_S390(...)
#endif /* IF_ARCH_S390 */

#ifndef IF_ARCH_MIPS
    #define IF_ARCH_MIPS(...)
#endif /* IF_ARCH_MIPS */

#ifndef IF_ARCH_SPARC
    #define IF_ARCH_SPARC(...)
#endif /* IF_ARCH_MIPS */

#ifndef ARCH_RISCV_ASM
    #define ARCH_RISCV_ASM(...)
#endif /* ARCH_RISCV_ASM */

#ifndef ARCH_RISCV64_ASM
    #define ARCH_RISCV64_ASM(...)
#endif /* ARCH_RISCV64_ASM */

#ifndef ARCH_RISCV32_ASM
    #define ARCH_RISCV32_ASM(...)
#endif /* ARCH_RISCV32_ASM */

#ifndef ARCH_LOONGARCH_ASM
    #define ARCH_LOONGARCH_ASM(...)
#endif /* ARCH_LOONGARCH_ASM */

#ifndef ARCH_LOONGARCH32ASM
    #define ARCH_LOONGARCH32_ASM(...)
#endif /* ARCH_LOONGARCH32_ASM */

#ifndef ARCH_LOONGARCH64ASM
    #define ARCH_LOONGARCH64_ASM(...)
#endif /* ARCH_LOONGARCH64_ASM */

//-----------------------------------------------------------------------------
// Default platform
#ifndef IF_PLATFORM_UNIX
    #define IF_PLATFORM_UNIX(...)
#endif /* IF_PLATFORM_UNIX */

#ifndef IF_PLATFORM_SOLARIS
    #define IF_PLATFORM_SOLARIS(...)
#endif /* IF_PLATFORM_SOLARIS */

#ifndef IF_PLATFORM_LINUX
    #define IF_PLATFORM_LINUX(...)
#endif /* IF_PLATFORM_LINUX */

#ifndef IF_PLATFORM_BSD
    #define IF_PLATFORM_BSD(...)
#endif /* IF_PLATFORM_BSD */

#ifndef IF_PLATFORM_MACOSX
    #define IF_PLATFORM_MACOSX(...)
#endif /* IF_PLATFORM_MACOSX */

#ifndef IF_PLATFORM_HAIKU
    #define IF_PLATFORM_HAIKU(...)
#endif /* IF_PLATFORM_HAIKU */

#ifndef IF_PLATFORM_POSIX
    #define IF_PLATFORM_POSIX(...)
#endif /* IF_PLATFORM_POSIX */

#ifndef IF_PLATFORM_WINDOWS
    #define IF_PLATFORM_WINDOWS(...)
#endif /* IF_PLATFORM_WINDOWS */

//-----------------------------------------------------------------------------
// Detect some libraries
#ifdef __GLIBC__
    #define USE_GLIBC                           __GLIBC__
#endif /* GLIBC */

//-----------------------------------------------------------------------------
// Optimizations
#ifdef ARCH_I386
    #define DEFAULT_ALIGN                   0x10
    #define MINIMUM_ALIGN                   0x08
#endif /* ARCH_X86 */

#ifdef ARCH_X86_64
    #define DEFAULT_ALIGN                   0x10
    #define MINIMUM_ALIGN                   0x08
#endif /* ARCH_X86 */

#ifdef ARCH_ARCH_ARM
    #define DEFAULT_ALIGN                   0x10
    #define MINIMUM_ALIGN                   0x08
#endif /* ARCH_ARM */

#ifdef ARCH_ARCH_AARCH64
    #define DEFAULT_ALIGN                   0x10
    #define MINIMUM_ALIGN                   0x08
#endif /* ARCH_ARM */

#ifndef DEFAULT_ALIGN
    #define DEFAULT_ALIGN                   0x10
#endif /* DEFAULT_ALIGN */

#ifndef MINIMUM_ALIGN
    #define MINIMUM_ALIGN                   DEFAULT_ALIGN
#endif /* DEFAULT_ALIGN */

#ifdef LSP_UNALIGNED_MEMORY_SAFE
    #define IF_UNALIGNED_MEMORY_SAFE(x)     x
    #define IF_UNALIGNED_MEMORY_UNSAFE(x)
#else
    #define IF_UNALIGNED_MEMORY_SAFE(x)
    #define IF_UNALIGNED_MEMORY_UNSAFE(x)   x
#endif /* LSP_UNALIGNED_MEMORY_SAFE */

#ifdef PLATFORM_LINUX
    #include <linux/limits.h>
#endif /* __linux__ */

//-----------------------------------------------------------------------------
// Character type sizes
#if (WCHAR_MAX >= 0x10000ul)
    #define WCHART_32BIT
#else
    #define WCHART_16BIT
#endif /* WCHAR_MAX */

#ifndef SIZE_MAX
    #define SIZE_MAX                        (~((size_t)(0)))
#endif /* SIZE_MAX */

#ifndef SSIZE_MAX
    #define SSIZE_MAX                       ((ssize_t)(SIZE_MAX >> 1))
#endif /* SIZE_MAX */

#ifndef PATH_MAX
    #define PATH_MAX                        4096
#endif /* PATH_MAX */

namespace lsp
{
    enum lsp_wrap_flags_t
    {
        WRAP_NONE       = 0,

        WRAP_CLOSE      = 1 << 0,
        WRAP_DELETE     = 1 << 1
    };

    enum lsp_memdrop_t
    {
        MEMDROP_NONE,
        MEMDROP_FREE,
        MEMDROP_DELETE,
        MEMDROP_ARR_DELETE
    };

    typedef uint64_t        wsize_t;
    typedef int64_t         wssize_t;

    /** Unicode character definition
     *
     */
    typedef uint32_t        lsp_wchar_t;
    typedef int32_t         lsp_swchar_t;

    #if defined(WCHART_16BIT)
        typedef wchar_t             lsp_utf16_t;
        typedef uint32_t            lsp_utf32_t;
    #else
        typedef uint16_t            lsp_utf16_t;
        typedef wchar_t             lsp_utf32_t;
    #endif
} /* namespace lsp */

//------------------------------------------------------------------------------
// Library exports, for built-in modules there are no exports
#ifdef PLATFORM_WINDOWS
    #define LSP_IMPORT_MODIFIER     __declspec(dllimport)
    #define LSP_EXPORT_MODIFIER     __declspec(dllexport)
    #define LSP_HIDDEN_MODIFIER
#else
    #define LSP_IMPORT_MODIFIER
    #define LSP_EXPORT_MODIFIER     __attribute__((visibility("default")))
    #define LSP_HIDDEN_MODIFIER     __attribute__((visibility("hidden")))
#endif /* PLATFORM_WINDOWS */

#ifdef __cplusplus
    #define LSP_SYMBOL_EXTERN       extern
    #define LSP_CSYMBOL_EXTERN      extern "C"
#else
    #define LSP_SYMBOL_EXTERN       extern
    #define LSP_CSYMBOL_EXTERN
#endif /* __cplusplus */

//------------------------------------------------------------------------------
// Library exports, for built-in modules there are no exports
namespace lsp
{
    template <class T>
    inline void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    inline T *release(T * &a)
    {
        T *tmp = a;
        a = NULL;
        return tmp;
    }

    template <class A, class B>
    inline A lsp_max(A a, B b)
    {
        return (a > b) ? a : b;
    }

    template <class A, class B, class C>
    inline A lsp_max(A a, B b, C c)
    {
        if ((a > b) && (a > c))
            return a;
        return (b > c) ? b : c;
    }

    template <class A, class B, class C, class D>
    inline A lsp_max(A a, B b, C c, D d)
    {
        return lsp_max(lsp_max(a, b), lsp_max(c, d));
    }

    template <class A, class B>
    inline A lsp_min(A a, B b)
    {
        return (a < b) ? a : b;
    }

    template <class A, class B, class C>
    inline A lsp_min(A a, B b, C c)
    {
        if ((a < b) && (a < c))
            return a;
        return (b < c) ? b : c;
    }

    template <class A, class B, class C, class D>
    inline A lsp_min(A a, B b, C c, D d)
    {
        return lsp_min(lsp_min(a, b), lsp_min(c, d));
    }

    template <class A, class B, class C>
    inline A lsp_limit(A a, B min, C max)
    {
        return (a < min) ? min : ((a > max) ? max : a);
    }

    template <class A, class B, class C>
    inline A lsp_xlimit(A a, B min, C max)
    {
        if (min < max)
            return (a < min) ? min : ((a > max) ? max : a);

        return (a < max) ? max : ((a > min) ? min : a);
    }

    template <class T>
    inline T lsp_abs(T a)
    {
        return (a < 0) ? -a : a;
    }

    template <class S, class F>
    inline S lsp_setflag(S bits, F flag, bool value)
    {
        return (value) ? bits | flag : bits & (~flag);
    }

    template <class T>
    inline T * release_ptr(T * & value)
    {
        T *res  = value;
        value   = nullptr;
        return res;
    }

    LSP_COMMON_LIB_PUBLIC
    int version_cmp(const version_t *a, const version_t *b);

    LSP_COMMON_LIB_PUBLIC
    int version_cmp(const version_t &a, const version_t &b);

    LSP_COMMON_LIB_PUBLIC
    bool version_copy(version_t *dst, const version_t *src);

    LSP_COMMON_LIB_PUBLIC
    void version_destroy(version_t *version);

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

#endif /* LSP_PLUG_IN_COMMON_TYPES_H_ */
