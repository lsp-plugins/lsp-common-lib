/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 5 июл. 2026 г.
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

#ifndef PRIVATE_ARCH_X86_CPUID_H_
#define PRIVATE_ARCH_X86_CPUID_H_

#include <lsp-plug.in/common/types.h>

#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/stdlib/stdio.h>

//-------------------------------------------------------------------------
// Processor microarchitecture detection

// Intel microarchitecture detection
#define INTEL_FAMILY_686_CORE               0x06

#define INTEL_MODEL_NEHALEM_D               0x1a
#define INTEL_MODEL_NEHALEM_M               0x1e
#define INTEL_MODEL_NEHALEM_EX              0x1f
#define INTEL_MODEL_WESTMERE_M              0x25
#define INTEL_MODEL_WESTMERE_S              0x2c
#define INTEL_MODEL_WESTMERE_EX             0x2f

#define INTEL_MODEL_SANDY_BRIDGE_D          0x2a
#define INTEL_MODEL_SANDY_BRIDGE_S          0x2d
#define INTEL_MODEL_IVY_BRIDGE_D            0x3a
#define INTEL_MODEL_IVY_BRIDGE_S            0x3e

#define INTEL_MODEL_HASWELL_D               0x3c
#define INTEL_MODEL_HASWELL_S               0x3f
#define INTEL_MODEL_HASWELL_M               0x45
#define INTEL_MODEL_HASWELL_ULT             0x46
#define INTEL_MODEL_BROADWELL_D             0x3d
#define INTEL_MODEL_BROADWELL_ULT           0x47
#define INTEL_MODEL_BROADWELL_S             0x4f
#define INTEL_MODEL_BROADWELL_DE            0x56

#define INTEL_MODEL_SKYLAKE_M               0x4e
#define INTEL_MODEL_SKYLAKE_S               0x55
#define INTEL_MODEL_SKYLAKE_D               0x5e
#define INTEL_MODEL_KABY_LAKE_M             0x8e
#define INTEL_MODEL_KABY_LAKE_D             0x9e

#define INTEL_MODEL_ICE_LAKE_S              0x6a
#define INTEL_MODEL_ICE_LAKE_DE             0x6c
#define INTEL_MODEL_ICE_LAKE_M              0x7d
#define INTEL_MODEL_ICE_LAKE_ULT            0x7e
#define INTEL_MODEL_TIGER_LAKE_M            0x8c
#define INTEL_MODEL_TIGER_LAKE_ULT          0x8d
#define INTEL_MODEL_ROCKET_LAKE_D           0xa7

#define INTEL_MODEL_ALDER_LAKE_D            0x97
#define INTEL_MODEL_ALDER_LAKE_M            0x9a
#define INTEL_MODEL_RAPTOR_LAKE_D           0xb7
#define INTEL_MODEL_RAPTOR_LAKE_M           0xba
#define INTEL_MODEL_RAPTOR_LAKE_HX          0xbf
#define INTEL_MODEL_METEOR_LAKE_M           0xaa
#define INTEL_MODEL_METEOR_LAKE_D           0xac

#define INTEL_MODEL_LUNAR_LAKE_M            0xbd
#define INTEL_MODEL_ARROW_LAKE_D            0xc5
#define INTEL_MODEL_ARROW_LAKE_M            0xc6
#define INTEL_MODEL_PANTHER_LAKE_M          0xcc

#define INTEL_MODEL_ATOM_SILVERMONT_D       0x37
#define INTEL_MODEL_ATOM_SILVERMONT_M       0x4a
#define INTEL_MODEL_ATOM_SILVERMONT_S       0x4d
#define INTEL_MODEL_ATOM_SILVERMONT_A       0x5a
#define INTEL_MODEL_ATOM_AIRMONT            0x4c
#define INTEL_MODEL_ATOM_GOLDMONT           0x5c
#define INTEL_MODEL_ATOM_GOLDMONT_S         0x75
#define INTEL_MODEL_ATOM_GOLDMONT_PLUS      0x7a
#define INTEL_MODEL_ATOM_TREMONT_S          0x86
#define INTEL_MODEL_ATOM_TREMONT_M          0x96
#define INTEL_MODEL_ATOM_TREMONT_D          0x9c
#define INTEL_MODEL_ATOM_GRACEMONT_M        0xbe

// AMD microarchitecture detection
#define AMD_FAMILY_K8_HAMMER                0x0f
#define AMD_FAMILY_K10                      0x10
#define AMD_FAMILY_K10_GRIFFIN              0x11
#define AMD_FAMILY_K10_LLANO                0x12
#define AMD_FAMILY_BOBCAT                   0x14
#define AMD_FAMILY_BULLDOZER                0x15
#define AMD_FAMILY_JAGUAR                   0x16
#define AMD_FAMILY_ZEN_1_2                  0x17
#define AMD_FAMILY_DHYANA                   0x18
#define AMD_FAMILY_ZEN_3_4                  0x19
#define AMD_FAMILY_ZEN_5                    0x1a

// Bulldozer/Piledriver/Steamroller/Excavator families
#define AMD_MODEL_BULLDOZER_MAX             0x0f
#define AMD_MODEL_PILEDRIVER_MIN            0x10
#define AMD_MODEL_PILEDRIVER_MAX            0x1f
#define AMD_MODEL_PILEDRIVER_ALT            0x02
#define AMD_MODEL_STEAMROLLER_MIN           0x30
#define AMD_MODEL_STEAMROLLER_MAX           0x3f
#define AMD_MODEL_EXCAVATOR_MIN             0x60
#define AMD_MODEL_EXCAVATOR_MAX             0x7f

// Jaguar/Puma families
#define AMD_MODEL_PUMA_MIN                  0x30

// Zen 1/Zen+/Zen 2 families
#define AMD_MODEL_ZEN1_MAX                  0x0f
#define AMD_MODEL_ZEN_PLUS_MIN              0x10
#define AMD_MODEL_ZEN_PLUS_MAX              0x1f
#define AMD_MODEL_ZEN_PLUS_ALT              0x08
#define AMD_MODEL_ZEN2_ZONE_A_MIN           0x30
#define AMD_MODEL_ZEN2_ZONE_A_MAX           0x4f
#define AMD_MODEL_ZEN2_ZONE_B_MIN           0x60
#define AMD_MODEL_ZEN2_ZONE_B_MAX           0x7f

// Zen 3/Zen 4 families
#define AMD_MODEL_ZEN4_ZONE_A_MIN           0x10
#define AMD_MODEL_ZEN4_ZONE_A_MAX           0x1f
#define AMD_MODEL_ZEN4_ZONE_B_MIN           0x60
#define AMD_MODEL_ZEN4_ZONE_B_MAX           0x7f
#define AMD_MODEL_ZEN4_ZONE_C_MIN           0xa0
#define AMD_MODEL_ZEN4_ZONE_C_MAX           0xaf

//-------------------------------------------------------------------------
// Function 1
#define X86_CPUID1_INTEL_ECX_SSE3           (1 << 0)
#define X86_CPUID1_INTEL_ECX_SSSE3          (1 << 9)
#define X86_CPUID1_INTEL_ECX_FMA3           (1 << 12)
#define X86_CPUID1_INTEL_ECX_SSE4_1         (1 << 19)
#define X86_CPUID1_INTEL_ECX_SSE4_2         (1 << 20)
#define X86_CPUID1_INTEL_ECX_MOVBE          (1 << 22)
#define X86_CPUID1_INTEL_ECX_XSAVE          (1 << 26)
#define X86_CPUID1_INTEL_ECX_OSXSAVE        (1 << 27)
#define X86_CPUID1_INTEL_ECX_AVX            (1 << 28)

#define X86_CPUID1_INTEL_EDX_FPU            (1 << 0)
#define X86_CPUID1_INTEL_EDX_CMOV           (1 << 15)
#define X86_CPUID1_INTEL_EDX_MMX            (1 << 23)
#define X86_CPUID1_INTEL_EDX_FXSR           (1 << 24)
#define X86_CPUID1_INTEL_EDX_SSE            (1 << 25)
#define X86_CPUID1_INTEL_EDX_SSE2           (1 << 26)

#define X86_CPUID1_AMD_ECX_SSE3             (1 << 0)
#define X86_CPUID1_AMD_ECX_SSSE3            (1 << 9)
#define X86_CPUID1_AMD_ECX_FMA3             (1 << 12)
#define X86_CPUID1_AMD_ECX_SSE4_1           (1 << 19)
#define X86_CPUID1_AMD_ECX_SSE4_2           (1 << 20)
#define X86_CPUID1_AMD_ECX_MOVBE            (1 << 22)
#define X86_CPUID1_AMD_ECX_XSAVE            (1 << 26)
#define X86_CPUID1_AMD_ECX_OSXSAVE          (1 << 27)
#define X86_CPUID1_AMD_ECX_AVX              (1 << 28)

#define X86_CPUID1_AMD_EDX_FPU              (1 << 0)
#define X86_CPUID1_AMD_EDX_CMOV             (1 << 15)
#define X86_CPUID1_AMD_EDX_MMX              (1 << 23)
#define X86_CPUID1_AMD_EDX_FXSR             (1 << 24)
#define X86_CPUID1_AMD_EDX_SSE              (1 << 25)
#define X86_CPUID1_AMD_EDX_SSE2             (1 << 26)

//-------------------------------------------------------------------------
// Function 7
#define X86_CPUID7_INTEL_EBX_AVX2           (1 << 5)
#define X86_CPUID7_INTEL_EBX_AVX512F        (1 << 16)
#define X86_CPUID7_INTEL_EBX_AVX512DQ       (1 << 17)
#define X86_CPUID7_INTEL_EBX_AVX512IFMA     (1 << 21)
#define X86_CPUID7_INTEL_EBX_AVX512PF       (1 << 26)
#define X86_CPUID7_INTEL_EBX_AVX512ER       (1 << 27)
#define X86_CPUID7_INTEL_EBX_AVX512CD       (1 << 28)
#define X86_CPUID7_INTEL_EBX_AVX512BW       (1 << 30)
#define X86_CPUID7_INTEL_EBX_AVX512VL       (1 << 31)

#define X86_CPUID7_INTEL_ECX_AVX512VBMI     (1 << 1)

#define X86_CPUID7_AMD_EBX_AVX2             (1 << 5)
#define X86_CPUID7_AMD_EBX_AVX512F          (1 << 16)
#define X86_CPUID7_AMD_EBX_AVX512DQ         (1 << 17)
#define X86_CPUID7_AMD_EBX_AVX512IFMA       (1 << 21)
#define X86_CPUID7_AMD_EBX_AVX512PF         (1 << 26)
#define X86_CPUID7_AMD_EBX_AVX512ER         (1 << 27)
#define X86_CPUID7_AMD_EBX_AVX512CD         (1 << 28)
#define X86_CPUID7_AMD_EBX_AVX512BW         (1 << 30)
#define X86_CPUID7_AMD_EBX_AVX512VL         (1 << 31)

#define X86_CPUID7_AMD_ECX_AVX512VBMI       (1 << 1)

//-------------------------------------------------------------------------
// Function 80000001
#define X86_XCPUID1_AMD_ECX_FMA4                (1 << 16)
#define X86_XCPUID1_AMD_ECX_SSE4A               (1 << 6)

#define X86_XCPUID1_AMD_EDX_FPU                 (1 << 0)
#define X86_XCPUID1_AMD_EDX_CMOV                (1 << 15)
#define X86_XCPUID1_AMD_EDX_MMX                 (1 << 23)

//-------------------------------------------------------------------------
// XCR0 register flags
#define XCR0_FLAG_FPU                           (1 << 0)
#define XCR0_FLAG_SSE                           (1 << 1)
#define XCR0_FLAG_AVX                           (1 << 2)
#define XCR0_FLAG_BNDREG                        (1 << 3)
#define XCR0_FLAG_BNDCSR                        (1 << 4)
#define XCR0_FLAG_OPMASK                        (1 << 5)
#define XCR0_FLAG_ZMM_HI256                     (1 << 6)
#define XCR0_FLAG_HI16_ZMM                      (1 << 7)
#define XCR0_FLAG_PKRU                          (1 << 8)

#define XCR_FLAGS_AVX                           (XCR0_FLAG_SSE | XCR0_FLAG_AVX)
#define XCR_FLAGS_AVX512                        (XCR_FLAGS_AVX | XCR0_FLAG_OPMASK | XCR0_FLAG_ZMM_HI256 | XCR0_FLAG_HI16_ZMM)

namespace lsp
{
    #pragma pack(push, 1)
    typedef struct cpuid_info_t
    {
        uint32_t        eax;
        uint32_t        ebx;
        uint32_t        ecx;
        uint32_t        edx;
    } cpuid_info_t;
    #pragma pack(pop)

    #pragma pack(push, 1)
    typedef union vendor_sig_t
    {
        char    sig[12];
        struct {
            uint32_t    ebx;
            uint32_t    edx;
            uint32_t    ecx;
        } reg;
    } vendor_sig_t;
    #pragma pack(pop)

    #if defined(ARCH_I386)
        static inline bool cpuid_supported()
        {
            bool result;
            ARCH_X86_ASM
            (
                __ASM_EMIT("pushfl")
                __ASM_EMIT("pop         %%eax")
                __ASM_EMIT("mov         %%eax, %%edx")
                __ASM_EMIT("xor         $0x200000, %%eax")
                __ASM_EMIT("push        %%eax")
                __ASM_EMIT("popfl")
                __ASM_EMIT("pushfl")
                __ASM_EMIT("pop         %%eax")
                __ASM_EMIT("xor         %%edx, %%eax")
                __ASM_EMIT("shr         $21, %%eax")
                __ASM_EMIT("and         $1, %%eax")
                : "=a"(result)
                : : "cc", "%edx"
            );

            return result;
        }
    #elif defined(ARCH_X86_64)
        static inline bool cpuid_supported()
        {
            return true;
        }
    #endif /* __i386__ */

    typedef struct cpu_vendor_id_t
    {
        const char         *signature;
        cpu_vendor_t        vendor_id;
    } vendors_t;

    static const cpu_vendor_id_t cpu_vendor_ids[] =
    {
        { "  Shanghai  ",   CPU_VENDOR_ZHAOXIN          },
        { " MCST Elbrus",   CPU_VENDOR_MCST             },
        { "AMDisbetter!",   CPU_VENDOR_AMD              },
        { "AuthenticAMD",   CPU_VENDOR_AMD              },
        { "CentaurHauls",   CPU_VENDOR_VIA              },
        { "CyrixInstead",   CPU_VENDOR_CYRIX            },
        { "E2K MACHINE ",   CPU_VENDOR_MCST             },
        { "Geode by NSC",   CPU_VENDOR_NSC              },
        { "GenuineIntel",   CPU_VENDOR_INTEL            },
        { "GenuineIotel",   CPU_VENDOR_INTEL            },
        { "Genuine RDC ",   CPU_VENDOR_RDCS             },
        { "GenuineTMx86",   CPU_VENDOR_TRANSMETA        },
        { "Geode by NSC",   CPU_VENDOR_NSC              },
        { "HygonGenuine",   CPU_VENDOR_HYGON            },
        { "NexGenDriven",   CPU_VENDOR_NEXGEN           },
        { "RiseRiseRise",   CPU_VENDOR_RISE             },
        { "SiS SiS SiS ",   CPU_VENDOR_SIS              },
        { "TransmetaCPU",   CPU_VENDOR_TRANSMETA        },
        { "UMC UMC UMC ",   CPU_VENDOR_UMC              },
        { "VIA VIA VIA ",   CPU_VENDOR_VIA              },
        { "Vortex86 SoC",   CPU_VENDOR_DMP_ELECTRONICS  },
    };

    static const char * const hwcap0_list[] =
    {
        "FPU", "CMOV", "MOVBE", "MMX",
        "FXSAVE", "SSE", "SSE2", "SSE3", "SSSE3",
        "SSE4.1", "SSE4.2", "SSE4A",
        "XSAVE", "FMA3", "FMA4", "AVX", "AVX2",
        "OSXSAVE", "AVX512F", "AVX512DQ", "AVX512IFMA",
        "AVX512PF", "AVX512ER", "AVX512CD", "AVX512BW",
        "AVX512VL", "AVX512VBMI",
        NULL
    };

    static inline bool cpuid(cpuid_info_t *info, uint32_t leaf, uint32_t subleaf)
    {
        ARCH_X86_ASM
        (
            __ASM_EMIT32("push      %%ebx")
            __ASM_EMIT("cpuid")
            __ASM_EMIT("mov         %%eax, 0x0(%[info])")
            __ASM_EMIT("mov         %%ebx, 0x4(%[info])")
            __ASM_EMIT("mov         %%ecx, 0x8(%[info])")
            __ASM_EMIT("mov         %%edx, 0xc(%[info])")
            __ASM_EMIT32("pop       %%ebx")

            : "+a"(leaf), "+c"(subleaf)
            : [info] "D" (info)
            : "cc", "memory",
              __IF_64("%ebx", )
              "%edx"
        );

        return true;
    }

    void read_brand_string(cpuid_info_t *info, uint32_t max_ext_cpuid, char *brand)
    {
        // FUNCTION 0x80000002 - 0x80000004
        if (max_ext_cpuid < 0x80000004)
        {
            strcpy(brand, "Generic " ARCH_STRING " processor");
            return;
        }

        uint32_t *dst = reinterpret_cast<uint32_t *>(brand);
        for (size_t i=0x80000002; i<=0x80000004; ++i)
        {
            cpuid(info, i, 0);
            *(dst++)    = info->eax;
            *(dst++)    = info->ebx;
            *(dst++)    = info->ecx;
            *(dst++)    = info->edx;
        }
        *dst        = 0;

        // Cut the end of the string if there are spaces
        char *end   = &brand[3 * 16 - 1];
        while ((end >= brand) && (((*end) == ' ') || ((*end) == '\0')))
            *(end--) = '\0';
        // Cut the start of the string if there are spaces
        char *start = brand;
        while ((start < end) && ((*start) == ' '))
            start++;
        if (start > brand)
            memmove(brand, start, end - start + 1);
    }

    static cpu_micro_t decode_intel_micro(uint32_t family, uint32_t model)
    {
        if (family != INTEL_FAMILY_686_CORE)
            return CPU_MICRO_UNKNOWN;
        else if (model >= INTEL_MODEL_PANTHER_LAKE_M)
            return CPU_MICRO_INTEL_PANTHER_LAKE;

        switch (model)
        {
            case INTEL_MODEL_NEHALEM_D:
            case INTEL_MODEL_NEHALEM_M:
            case INTEL_MODEL_NEHALEM_EX:
                return CPU_MICRO_INTEL_NEHALEM;

            case INTEL_MODEL_WESTMERE_M:
            case INTEL_MODEL_WESTMERE_S:
            case INTEL_MODEL_WESTMERE_EX:
                return CPU_MICRO_INTEL_WESTMERE;

            case INTEL_MODEL_SANDY_BRIDGE_D:
            case INTEL_MODEL_SANDY_BRIDGE_S:
                return CPU_MICRO_INTEL_SANDY_BRIDGE;

            case INTEL_MODEL_IVY_BRIDGE_D:
            case INTEL_MODEL_IVY_BRIDGE_S:
                return CPU_MICRO_INTEL_IVY_BRIDGE;

            case INTEL_MODEL_HASWELL_D:
            case INTEL_MODEL_HASWELL_S:
            case INTEL_MODEL_HASWELL_M:
            case INTEL_MODEL_HASWELL_ULT:
                return CPU_MICRO_INTEL_HASWELL;

            case INTEL_MODEL_BROADWELL_D:
            case INTEL_MODEL_BROADWELL_ULT:
            case INTEL_MODEL_BROADWELL_S:
            case INTEL_MODEL_BROADWELL_DE:
                return CPU_MICRO_INTEL_BROADWELL;

            case INTEL_MODEL_SKYLAKE_M:
            case INTEL_MODEL_SKYLAKE_S:
            case INTEL_MODEL_SKYLAKE_D:
                return CPU_MICRO_INTEL_SKYLAKE;

            case INTEL_MODEL_KABY_LAKE_M:
            case INTEL_MODEL_KABY_LAKE_D:
                return CPU_MICRO_INTEL_KABY_LAKE;

            case INTEL_MODEL_ICE_LAKE_S:
            case INTEL_MODEL_ICE_LAKE_DE:
            case INTEL_MODEL_ICE_LAKE_M:
            case INTEL_MODEL_ICE_LAKE_ULT:
                return CPU_MICRO_INTEL_ICE_LAKE;

            case INTEL_MODEL_TIGER_LAKE_M:
            case INTEL_MODEL_TIGER_LAKE_ULT:
                return CPU_MICRO_INTEL_TIGER_LAKE;

            case INTEL_MODEL_ROCKET_LAKE_D:
                return CPU_MICRO_INTEL_ROCKET_LAKE;

            case INTEL_MODEL_ALDER_LAKE_D:
            case INTEL_MODEL_ALDER_LAKE_M:
                return CPU_MICRO_INTEL_ALDER_LAKE;

            case INTEL_MODEL_RAPTOR_LAKE_D:
            case INTEL_MODEL_RAPTOR_LAKE_M:
            case INTEL_MODEL_RAPTOR_LAKE_HX:
                return CPU_MICRO_INTEL_RAPTOR_LAKE;

            case INTEL_MODEL_METEOR_LAKE_M:
            case INTEL_MODEL_METEOR_LAKE_D:
                return CPU_MICRO_INTEL_METEOR_LAKE;

            case INTEL_MODEL_LUNAR_LAKE_M:
            case INTEL_MODEL_ARROW_LAKE_D:
            case INTEL_MODEL_ARROW_LAKE_M:
                return CPU_MICRO_INTEL_LUNAR_LAKE;

            case INTEL_MODEL_PANTHER_LAKE_M:
                return CPU_MICRO_INTEL_PANTHER_LAKE;

            case INTEL_MODEL_ATOM_SILVERMONT_D:
            case INTEL_MODEL_ATOM_SILVERMONT_M:
            case INTEL_MODEL_ATOM_SILVERMONT_S:
            case INTEL_MODEL_ATOM_SILVERMONT_A:
                return CPU_MICRO_INTEL_SILVERMONT;

            case INTEL_MODEL_ATOM_AIRMONT:
                return CPU_MICRO_INTEL_AIRMONT;

            case INTEL_MODEL_ATOM_GOLDMONT:
            case INTEL_MODEL_ATOM_GOLDMONT_S:
                return CPU_MICRO_INTEL_GOLDMONT;

            case INTEL_MODEL_ATOM_GOLDMONT_PLUS:
                return CPU_MICRO_INTEL_GOLDMONT_PLUS;

            case INTEL_MODEL_ATOM_TREMONT_S:
            case INTEL_MODEL_ATOM_TREMONT_M:
                return CPU_MICRO_INTEL_TREMONT;

            case INTEL_MODEL_ATOM_TREMONT_D:
                return CPU_MICRO_INTEL_JASPER_LAKE;
            case INTEL_MODEL_ATOM_GRACEMONT_M:
                return CPU_MICRO_INTEL_ALDER_LAKE_N;

            default:
                break;
        }

        return CPU_MICRO_UNKNOWN;
    }

    static cpu_micro_t decode_amd_micro(uint32_t family, uint32_t model)
    {
        if (family >= AMD_FAMILY_ZEN_5)
            return CPU_MICRO_AMD_ZEN5;

        switch (family)
        {
            case AMD_FAMILY_K8_HAMMER:
                return CPU_MICRO_AMD_K8_HAMMER;

            case AMD_FAMILY_K10:
                return CPU_MICRO_AMD_K10;

            case AMD_FAMILY_K10_GRIFFIN:
                return CPU_MICRO_AMD_K10_GRIFFIN;

            case AMD_FAMILY_K10_LLANO:
                return CPU_MICRO_AMD_K10_LLANO;

            case AMD_FAMILY_BOBCAT:
                return CPU_MICRO_AMD_BOBCAT;

            case AMD_FAMILY_DHYANA:
                return CPU_MICRO_AMD_DHYANA;

            case AMD_FAMILY_JAGUAR:
                return (model >= AMD_MODEL_PUMA_MIN) ? CPU_MICRO_AMD_PUMA : CPU_MICRO_AMD_JAGUAR;

            case AMD_FAMILY_BULLDOZER:
                if ((model >= AMD_MODEL_EXCAVATOR_MIN) && (model <= AMD_MODEL_EXCAVATOR_MAX))
                    return CPU_MICRO_AMD_EXCAVATOR;
                if ((model >= AMD_MODEL_STEAMROLLER_MIN) && (model <= AMD_MODEL_STEAMROLLER_MAX))
                    return CPU_MICRO_AMD_STEAMROLLER;
                if (((model >= AMD_MODEL_PILEDRIVER_MIN) && (model <= AMD_MODEL_PILEDRIVER_MAX)) ||
                    (model == AMD_MODEL_PILEDRIVER_ALT))
                    return CPU_MICRO_AMD_PILEDRIVER;
                if (model <= AMD_MODEL_BULLDOZER_MAX)
                    return CPU_MICRO_AMD_BULLDOZER;
                break;

            case AMD_FAMILY_ZEN_1_2:
                if (((model >= AMD_MODEL_ZEN2_ZONE_A_MIN) && (model <= AMD_MODEL_ZEN2_ZONE_A_MAX)) ||
                    ((model >= AMD_MODEL_ZEN2_ZONE_B_MIN) && (model <= AMD_MODEL_ZEN2_ZONE_B_MAX)))
                    return CPU_MICRO_AMD_ZEN2;

                if (((model >= AMD_MODEL_ZEN_PLUS_MIN) && (model <= AMD_MODEL_ZEN_PLUS_MAX)) ||
                    (model == AMD_MODEL_ZEN_PLUS_ALT))
                    return CPU_MICRO_AMD_ZEN_PLUS;

                if (model <= AMD_MODEL_ZEN1_MAX)
                    return CPU_MICRO_AMD_ZEN1;
                break;

            case AMD_FAMILY_ZEN_3_4:
                return (((model >= AMD_MODEL_ZEN4_ZONE_A_MIN) && (model <= AMD_MODEL_ZEN4_ZONE_A_MAX)) ||
                    ((model >= AMD_MODEL_ZEN4_ZONE_B_MIN) && (model <= AMD_MODEL_ZEN4_ZONE_B_MAX)) ||
                    ((model >= AMD_MODEL_ZEN4_ZONE_C_MIN) && (model <= AMD_MODEL_ZEN4_ZONE_C_MAX))) ?
                    CPU_MICRO_AMD_ZEN4 : CPU_MICRO_AMD_ZEN3;

            default:
                break;
        }

        return CPU_MICRO_UNKNOWN;
    }

    static inline uint64_t read_xcr(umword_t xcr_id)
    {
        uint64_t xcr;

        ARCH_X86_ASM
        (
            __ASM_EMIT64("xor       %%rax, %%rax")
            __ASM_EMIT(".byte       0x0f, 0x01, 0xd0")        // call xgetbv
            __ASM_EMIT64("shl       $32, %%rdx")
            __ASM_EMIT64("or        %%rdx, %%rax")
            : __IF_32("=A" (xcr)) __IF_64("=a" (xcr))
            : "c" (xcr_id)
            : __IF_64("%rdx")
        );
        return xcr;
    }

    static void intel_cpuid_impl(cpuid_t *f, uint32_t max_cpuid, uint32_t max_ext_cpuid)
    {
        cpuid_info_t info;
        uint32_t hwcap0 = 0;
        uint32_t xcr0   = 0;

        // FUNCTION 1
        if (max_cpuid >= 1)
        {
            cpuid(&info, 1, 0);

            if (info.edx & X86_CPUID1_INTEL_EDX_FPU)
                hwcap0          |= CPU_HWCAP0_FPU;
            if (info.edx & X86_CPUID1_INTEL_EDX_CMOV)
                hwcap0          |= CPU_HWCAP0_CMOV;
            if (info.edx & X86_CPUID1_INTEL_EDX_MMX)
                hwcap0          |= CPU_HWCAP0_MMX;
            if (info.edx & X86_CPUID1_INTEL_EDX_FXSR)
                hwcap0          |= CPU_HWCAP0_FXSAVE;
            if (info.edx & X86_CPUID1_INTEL_EDX_SSE)
                hwcap0          |= CPU_HWCAP0_SSE;
            if (info.edx & X86_CPUID1_INTEL_EDX_SSE2)
                hwcap0          |= CPU_HWCAP0_SSE2;

            if (info.ecx & X86_CPUID1_INTEL_ECX_MOVBE)
                hwcap0          |= CPU_HWCAP0_MOVBE;
            if (info.ecx & X86_CPUID1_INTEL_ECX_SSE3)
                hwcap0          |= CPU_HWCAP0_SSE3;
            if (info.ecx & X86_CPUID1_INTEL_ECX_SSSE3)
                hwcap0          |= CPU_HWCAP0_SSSE3;
            if (info.ecx & X86_CPUID1_INTEL_ECX_SSE4_1)
                hwcap0          |= CPU_HWCAP0_SSE4_1;
            if (info.ecx & X86_CPUID1_INTEL_ECX_SSE4_2)
                hwcap0          |= CPU_HWCAP0_SSE4_2;
            if (info.ecx & X86_CPUID1_INTEL_ECX_XSAVE)
                hwcap0          |= CPU_HWCAP0_XSAVE;
            if (info.ecx & X86_CPUID1_INTEL_ECX_OSXSAVE)
            {
                hwcap0             |= CPU_HWCAP0_OSXSAVE;
                xcr0                = read_xcr(0);

                // Additional check for AVX support
                if ((xcr0 & XCR_FLAGS_AVX) == XCR_FLAGS_AVX)
                {
                    if (info.ecx & X86_CPUID1_INTEL_ECX_FMA3)
                        hwcap0         |= CPU_HWCAP0_FMA3;
                    if (info.ecx & X86_CPUID1_INTEL_ECX_AVX)
                        hwcap0         |= CPU_HWCAP0_AVX;
                }
            }
        }

        // FUNCTION 7
        if (max_cpuid >= 7)
        {
            cpuid(&info, 7, 0);

            // Additional check for AVX2 support
            if ((xcr0 & XCR_FLAGS_AVX) == XCR_FLAGS_AVX)
            {
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX2)
                    hwcap0          |= CPU_HWCAP0_AVX2;
            }

            // Additional check for AVX512 support
            if ((xcr0 & XCR_FLAGS_AVX512) == XCR_FLAGS_AVX512)
            {
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512F)
                    hwcap0          |= CPU_HWCAP0_AVX512F;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512DQ)
                    hwcap0          |= CPU_HWCAP0_AVX512DQ;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512IFMA)
                    hwcap0          |= CPU_HWCAP0_AVX512IFMA;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512PF)
                    hwcap0          |= CPU_HWCAP0_AVX512PF;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512ER)
                    hwcap0          |= CPU_HWCAP0_AVX512ER;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512CD)
                    hwcap0          |= CPU_HWCAP0_AVX512CD;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512BW)
                    hwcap0          |= CPU_HWCAP0_AVX512BW;
                if (info.ebx & X86_CPUID7_INTEL_EBX_AVX512VL)
                    hwcap0          |= CPU_HWCAP0_AVX512VL;

                if (info.ecx & X86_CPUID7_INTEL_ECX_AVX512VBMI)
                    hwcap0          |= CPU_HWCAP0_AVX512VBMI;
            }
        }

        // Store hardware capabilities
        f->hwcap[0]     = hwcap0;
        f->hwcap[1]     = 0;
    }

    static void amd_cpuid_impl(cpuid_t *f, uint32_t max_cpuid, uint32_t max_ext_cpuid)
    {
        cpuid_info_t info;
        uint32_t hwcap0 = 0;
        uint32_t xcr0   = 0;

        // FUNCTION 1
        if (max_cpuid >= 1)
        {
            cpuid(&info, 1, 0);

            if (info.edx & X86_CPUID1_AMD_EDX_FPU)
                hwcap0          |= CPU_HWCAP0_FPU;
            if (info.edx & X86_CPUID1_AMD_EDX_FXSR)
                hwcap0          |= CPU_HWCAP0_FXSAVE;
            if (info.edx & X86_CPUID1_AMD_EDX_CMOV)
                hwcap0          |= CPU_HWCAP0_CMOV;
            if (info.edx & X86_CPUID1_AMD_EDX_MMX)
                hwcap0          |= CPU_HWCAP0_MMX;
            if (info.edx & X86_CPUID1_AMD_EDX_SSE)
                hwcap0          |= CPU_HWCAP0_SSE;
            if (info.edx & X86_CPUID1_AMD_EDX_SSE2)
                hwcap0          |= CPU_HWCAP0_SSE2;

            if (info.ecx & X86_CPUID1_AMD_ECX_MOVBE)
                hwcap0          |= CPU_HWCAP0_MOVBE;
            if (info.ecx & X86_CPUID1_AMD_ECX_SSE3)
                hwcap0          |= CPU_HWCAP0_SSE3;
            if (info.ecx & X86_CPUID1_AMD_ECX_SSSE3)
                hwcap0          |= CPU_HWCAP0_SSSE3;
            if (info.ecx & X86_CPUID1_AMD_ECX_SSE4_1)
                hwcap0          |= CPU_HWCAP0_SSE4_1;
            if (info.ecx & X86_CPUID1_AMD_ECX_SSE4_2)
                hwcap0          |= CPU_HWCAP0_SSE4_2;
            if (info.ecx & X86_CPUID1_AMD_ECX_XSAVE)
                hwcap0          |= CPU_HWCAP0_XSAVE;
            if (info.ecx & X86_CPUID1_AMD_ECX_OSXSAVE)
            {
                hwcap0             |= CPU_HWCAP0_OSXSAVE;
                xcr0                = read_xcr(0);

                // Additional check for AVX support
                if ((xcr0 & XCR_FLAGS_AVX) == XCR_FLAGS_AVX)
                {
                    if (info.ecx & X86_CPUID1_AMD_ECX_FMA3)
                        hwcap0         |= CPU_HWCAP0_FMA3;
                    if (info.ecx & X86_CPUID1_AMD_ECX_AVX)
                        hwcap0         |= CPU_HWCAP0_AVX;
                }
            }
        }

        // FUNCTION 7
        if (max_cpuid >= 7)
        {
            cpuid(&info, 7, 0);

            // Additional check for AVX2 support
            if ((xcr0 & XCR_FLAGS_AVX) == XCR_FLAGS_AVX)
            {
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX2)
                    hwcap0         |= CPU_HWCAP0_AVX2;
            }

            // Additional check for AVX512 support
            if ((xcr0 & XCR_FLAGS_AVX512) == XCR_FLAGS_AVX512)
            {
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512F)
                    hwcap0         |= CPU_HWCAP0_AVX512F;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512DQ)
                    hwcap0         |= CPU_HWCAP0_AVX512DQ;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512IFMA)
                    hwcap0         |= CPU_HWCAP0_AVX512IFMA;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512PF)
                    hwcap0         |= CPU_HWCAP0_AVX512PF;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512ER)
                    hwcap0         |= CPU_HWCAP0_AVX512ER;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512CD)
                    hwcap0         |= CPU_HWCAP0_AVX512CD;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512BW)
                    hwcap0         |= CPU_HWCAP0_AVX512BW;
                if (info.ebx & X86_CPUID7_AMD_EBX_AVX512VL)
                    hwcap0         |= CPU_HWCAP0_AVX512VL;

                if (info.ecx & X86_CPUID7_AMD_ECX_AVX512VBMI)
                    hwcap0         |= CPU_HWCAP0_AVX512VBMI;
            }
        }

        // FUNCTION 0x80000001
        if (max_ext_cpuid >= 0x80000001)
        {
            cpuid(&info, 0x80000001, 0);

            if (info.ecx & X86_XCPUID1_AMD_ECX_SSE4A)
                hwcap0          |= CPU_HWCAP0_SSE4A;

            if (info.edx & X86_XCPUID1_AMD_EDX_FPU)
                hwcap0          |= CPU_HWCAP0_FPU;
            if (info.edx & X86_XCPUID1_AMD_EDX_CMOV)
                hwcap0          |= CPU_HWCAP0_CMOV;
            if (info.edx & X86_XCPUID1_AMD_EDX_MMX)
                hwcap0          |= CPU_HWCAP0_MMX;

            // Additional check for FMA4 support
            if ((xcr0 & XCR_FLAGS_AVX) == XCR_FLAGS_AVX)
            {
                if (info.ecx & X86_XCPUID1_AMD_ECX_FMA4)
                    hwcap0         |= CPU_HWCAP0_FMA4;
            }
        }

        // Store hardware capabilities
        f->hwcap[0]     = hwcap0;
        f->hwcap[1]     = 0;
    }

    void cpuid_impl(cpuid_t *f)
    {
        if (!cpuid_supported())
            return;

        // Check max CPUID
        cpuid_info_t info;
        cpuid(&info, 0, 0);

        // Detect vendor
        vendor_sig_t sig;
        sig.reg.ebx     = info.ebx;
        sig.reg.ecx     = info.ecx;
        sig.reg.edx     = info.edx;

        for (size_t i=0, n=sizeof(cpu_vendor_ids)/sizeof(cpu_vendor_id_t); i<n; ++i)
        {
            if (!memcmp(sig.sig, cpu_vendor_ids[i].signature, sizeof(vendor_sig_t)))
            {
                f->vendor   = cpu_vendor_ids[i].vendor_id;
                break;
            }
        }

        const uint32_t max_cpuid    = info.eax;
        if (max_cpuid <= 0)
            return;

        // Get model and family
        cpuid(&info, 1, 0);
        uint32_t model      = (info.eax >> 4) & 0x0f;
        uint32_t family     = (info.eax >> 8) & 0x0f;

        switch (family)
        {
            case 3:
                f->arch = CPU_ARCH_I386;
                break;
            case 4:
                f->arch = CPU_ARCH_I486;
                break;
            case 5:
                f->arch = CPU_ARCH_I586;
                break;
            case 6:
            case 0x0f:
                #ifdef ARCH_X86_64
                    f->arch = CPU_ARCH_X86_64;
                #else
                    f->arch = CPU_ARCH_I686;
                #endif
                break;
            default:
                f->arch     = CPU_ARCH_UNKNOWN;
                break;
        }

        // Update model and family to extended model and family
        if ((family == 0x0f) || (family == 0x06))
            model              += (info.eax >> 12) & 0xf0;
        if (family == 0x0f)
            family             += (info.eax >> 20) & 0xff;

        f->model            = model;
        f->variant          = family;
        f->revision         = 0;

        // Get maximum available extended CPUID
        cpuid(&info, 0x80000000, 0);
        const uint32_t max_ext_cpuid    = info.eax;

        switch (f->vendor)
        {
            case CPU_VENDOR_INTEL:
                f->micro        = decode_intel_micro(family, model);
                intel_cpuid_impl(f, max_cpuid, max_ext_cpuid);
                break;

            case CPU_VENDOR_AMD:
            case CPU_VENDOR_HYGON:
                f->micro        = decode_amd_micro(family, model);
                amd_cpuid_impl(f, max_cpuid, max_ext_cpuid);
                break;

            default:
                break;
        }

        read_brand_string(&info, max_ext_cpuid, f->name);
    }

    cpuinfo_t *cpuinfo(const cpuid_t *features)
    {
        const char *vendor  = cpu_vendor(features->vendor);
        const char *arch    = cpu_arch(features->arch);
        const char *micro   = cpu_micro(features->micro);
        const char *name    = features->name;
        char *model         = NULL;

        const int n = asprintf(
            &model,
            "family=0x%x, model=0x%x",
            int(features->variant), int(features->model));
        if ((n < 0) || (model == NULL))
            return NULL;
        lsp_finally { free(model); };

        const size_t szof   =
            sizeof(cpuinfo_t) +
            strlen(name) + 1 +
            strlen(model) + 1 +
            estimate_hwcap_strlen(hwcap0_list, features->hwcap[0]) + 1;

        cpuinfo_t * const res   = malloc_bytes<cpuinfo_t>(szof);
        if (res == NULL)
            return res;

        char *text          = reinterpret_cast<char *>(&res[1]);

        res->vendor         = vendor;
        res->arch           = arch;
        res->micro          = micro;
        res->name           = text;
        text                = stpcpy(text, features->name) + 1;
        res->model          = text;
        text                = stpcpy(text, model) + 1;
        res->features       = text;
        fill_hwcap_str(text, hwcap0_list, features->hwcap[0]);

        return res;
    }

} /* namespace lsp */

#endif /* PRIVATE_ARCH_X86_CPUID_H_ */
