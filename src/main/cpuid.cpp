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

#include <lsp-plug.in/common/atomic.h>
#include <lsp-plug.in/common/cpuid.h>
#include <lsp-plug.in/stdlib/string.h>

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <processthreadsapi.h>
#else
    #include <sched.h>
#endif /* PLATFORM_WINDOWS */

namespace lsp
{
    size_t estimate_hwcap_strlen(const char * const * features, uint32_t hwcap)
    {
        // Estimate the string length
        size_t estimate = 0;
        for (const char * const *p = features; (hwcap != 0) && (p != NULL) && (*p != NULL); ++p)
        {
            if (hwcap & 1)
            {
                estimate += strlen(*p);
                hwcap >>= 1;
                if (hwcap)
                    ++estimate; // Space character
            }
            else
                hwcap >>= 1;
        }
        return estimate;
    }

    char *fill_hwcap_str(char *dst, const char * const * features, uint32_t hwcap)
    {
        // Build string
        char *s = dst;

        for (const char * const *p = features; (hwcap != 0) && (p != NULL) && (*p != NULL); ++p)
        {
            if (hwcap & 1)
            {
                s = stpcpy(s, *p);
                hwcap >>= 1;
                if (hwcap)
                    *(s++) = ' ';
            }
            else
                hwcap >>= 1;
        }
        *s = '\0';

        return s;
    }
} /* namespace lsp */

#if defined(ARCH_I386) || defined(ARCH_X86_64)
    #include <private/common/arch/x86/cpuid.h>
#elif defined(ARCH_AARCH64)
    #include <private/common/arch/aarch64/cpuid.h>
#elif defined(ARCH_ARM)
    #include <private/common/arch/arm/cpuid.h>
#else
    #include <private/common/arch/generic/cpuid.h>
#endif

namespace lsp
{
#ifdef PLATFORM_WINDOWS
    static void thread_yield()
    {
        SwitchToThread();
    }
#else
    static void thread_yield()
    {
        sched_yield();
    }
#endif /* PLATFORM_WINDOWS */

    static const char * const cpu_vendors[] =
    {
        "Unknown",
        "AMD",
        "Ampere",
        "APM",
        "Apple",
        "ARM",
        "Broadcom",
        "Cavium",
        "Cyrix",
        "DEC",
        "DM&P Electronics",
        "Faraday",
        "Fujitsu",
        "Hygon",
        "Infineon",
        "Intel",
        "Loongson",
        "Marvell",
        "MCST",
        "Microsoft",
        "Motorola",
        "Nexgen",
        "NSC",
        "NVidia",
        "Phytium",
        "Qualcomm",
        "RDC Semiconductor",
        "Rise",
        "Samsung",
        "SIS",
        "Texas Instruments",
        "Transmeta",
        "TSMC",
        "UMC",
        "VIA",
        "Zhaoxin",
    };

    static const char * const cpu_archs[] =
    {
        "Unknown",

        "i386",
        "i486",
        "i586",
        "i686",
        "x86_64",

        "ARMv5",
        "ARMv6",
        "ARMv7",
        "ARMv8",
        "ARMv9",

        "RISCV32",
        "RISCV64",
        "RISCV128",

        "LoongArch32",
        "LoongArch64",

        "PPC",
        "PPC64",

        "MIPS32",
        "MIPS64",

        "S390",
        "SPARC",
    };

    static const char * const cpu_micros[] =
    {
        "Unknown",

        "K8 Hammer",
        "K10",
        "K10/Griffin",
        "K10/Llano",
        "Bobcat",
        "Bulldozer",
        "Piledriver",
        "Steamroller",
        "Excavator",
        "Jaguar",
        "Puma",
        "Zen 1",
        "Zen+",
        "Zen 2",
        "Dhyana",
        "Zen 3",
        "Zen 4",
        "Zen 5",

        "Nehalem",
        "Westmere",
        "Sandy Bridge",
        "Ivy Bridge",
        "Haswell",
        "Silvermont",
        "Airmont",
        "Broadwell",
        "Skylake",
        "Goldmont",
        "Kaby Lake/Coffee Lake/Comet Lake",
        "Goldmont Plus/Gemini Lake",
        "Ice Lake",
        "Tremont",
        "Jasper Lake",
        "Tiger Lake",
        "Rocket Lake",
        "Alder Lake",
        "Raptor Lake",
        "Alder Lake N",
        "Metero Lake",
        "Lunar Lake/Arrow Lake",
        "Panther Lake",
    };

    enum cpuid_flags_t
    {
        CPUID_SET               = 1 << 0,
        CPUID_LOCK              = 1 << 1,
    };

    static uint32_t             cpuid_state = 0;
    static cpuid_t              cpuid_cache;

    void cpuid(cpuid_t *features, bool force)
    {
        // Check if we need a forced CPUID
        uint32_t state      = atomic_load(&cpuid_state);
        if (!(state & CPUID_SET))
            force               = true;

        // Call the CPUID implementation
        if (force)
        {
            bzero(features, sizeof(cpuid_t));
            cpuid_impl(features);
        }

        // Acquire lock
        do
        {
            state               = atomic_load(&cpuid_state);
            if (state & CPUID_LOCK)
            {
                thread_yield();
                continue;
            }

        } while (!atomic_cas(&cpuid_state, state, state | CPUID_LOCK | CPUID_SET));

        lsp_finally {
            // Release lock
            while (true)
            {
                state               = atomic_load(&cpuid_state);
                if (atomic_cas(&cpuid_state, state, state & (~CPUID_LOCK)))
                    break;
                thread_yield();
            }
        };

        // Sync cache state and result
        if (force)
            memcpy(&cpuid_cache, features, sizeof(cpuid_t));
        else
            memcpy(features, &cpuid_cache, sizeof(cpuid_t));
    }

    const char *cpu_vendor(cpu_vendor_t vendor)
    {
        constexpr size_t max_vendor_id = sizeof(cpu_vendors)/sizeof(cpu_vendors[0]);
        return (vendor < max_vendor_id) ? cpu_vendors[vendor] : cpu_vendors[0];
    }

    const char *cpu_arch(cpu_arch_t arch)
    {
        constexpr size_t max_arch_id = sizeof(cpu_archs)/sizeof(cpu_archs[0]);
        return (arch < max_arch_id) ? cpu_archs[arch] : cpu_archs[0];
    }

    const char *cpu_micro(cpu_micro_t micro)
    {
        constexpr size_t max_micro_id = sizeof(cpu_micros)/sizeof(cpu_micros[0]);
        return (micro < max_micro_id) ? cpu_micros[micro] : cpu_micros[0];
    }

} /* namespace lsp */


