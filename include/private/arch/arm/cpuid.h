/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 6 июл. 2026 г.
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

#ifndef PRIVATE_ARCH_ARM_CPUID_H_
#define PRIVATE_ARCH_ARM_CPUID_H_

#include <lsp-plug.in/common/types.h>

#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/stdlib/stdio.h>
#include <lsp-plug.in/stdlib/stdlib.h>

#include <errno.h>

// Platform-specific includes
#if defined(PLATFORM_FREEBSD)
    #include <sys/sysctl.h>
#elif defined(PLATFORM_MACOSX)
    #include <sys/sysctl.h>
#endif

#if !defined(PLATFORM_MACOSX)
    #include <sys/auxv.h>
#endif /* PLATFORM_POSIX */

#define DEFAULT_CPU_NAME            "Generic ARM processor"

// Redefine constants to be compatible with GCC 6.x (Raspbian) and GCC 8.x (FreeBSD)
#if defined(HWCAP_SWP) && !defined(HWCAP_ARM_SWP)
    #define HWCAP_ARM_SWP HWCAP_SWP
#endif
#if defined(HWCAP_HALF) && !defined(HWCAP_ARM_HALF)
    #define HWCAP_ARM_HALF HWCAP_HALF
#endif
#if defined(HWCAP_THUMB) && !defined(HWCAP_ARM_THUMB)
    #define HWCAP_ARM_THUMB HWCAP_THUMB
#endif
#if defined(HWCAP_26BIT) && !defined(HWCAP_ARM_26BIT)
    #define HWCAP_ARM_26BIT HWCAP_26BIT
#endif
#if defined(HWCAP_FAST_MULT) && !defined(HWCAP_ARM_FAST_MULT)
    #define HWCAP_ARM_FAST_MULT HWCAP_FAST_MULT
#endif
#if defined(HWCAP_FPA) && !defined(HWCAP_ARM_FPA)
    #define HWCAP_ARM_FPA HWCAP_FPA
#endif
#if defined(HWCAP_VFP) && !defined(HWCAP_ARM_VFP)
    #define HWCAP_ARM_VFP HWCAP_VFP
#endif
#if defined(HWCAP_EDSP) && !defined(HWCAP_ARM_EDSP)
    #define HWCAP_ARM_EDSP HWCAP_EDSP
#endif
#if defined(HWCAP_JAVA) && !defined(HWCAP_ARM_JAVA)
    #define HWCAP_ARM_JAVA HWCAP_JAVA
#endif
#if defined(HWCAP_IWMMXT) && !defined(HWCAP_ARM_IWMMXT)
    #define HWCAP_ARM_IWMMXT HWCAP_IWMMXT
#endif
#if defined(HWCAP_CRUNCH) && !defined(HWCAP_ARM_CRUNCH)
    #define HWCAP_ARM_CRUNCH HWCAP_CRUNCH
#endif
#if defined(HWCAP_THUMBEE) && !defined(HWCAP_ARM_THUMBEE)
    #define HWCAP_ARM_THUMBEE HWCAP_THUMBEE
#endif
#if defined(HWCAP_NEON) && !defined(HWCAP_ARM_NEON)
    #define HWCAP_ARM_NEON HWCAP_NEON
#endif
#if defined(HWCAP_VFPv3) && !defined(HWCAP_ARM_VFPv3)
    #define HWCAP_ARM_VFPv3 HWCAP_VFPv3
#endif
#if defined(HWCAP_VFPv3D16) && !defined(HWCAP_ARM_VFPv3D16)
    #define HWCAP_ARM_VFPv3D16 HWCAP_VFPv3D16
#endif
#if defined(HWCAP_TLS) && !defined(HWCAP_ARM_TLS)
    #define HWCAP_ARM_TLS HWCAP_TLS
#endif
#if defined(HWCAP_VFPv4) && !defined(HWCAP_ARM_VFPv4)
    #define HWCAP_ARM_VFPv4 HWCAP_VFPv4
#endif
#if defined(HWCAP_IDIVA) && !defined(HWCAP_ARM_IDIVA)
    #define HWCAP_ARM_IDIVA HWCAP_IDIVA
#endif
#if defined(HWCAP_IDIVT) && !defined(HWCAP_ARM_IDIVT)
    #define HWCAP_ARM_IDIVT HWCAP_IDIVT
#endif
#if defined(HWCAP_VFPD32) && !defined(HWCAP_ARM_VFPD32)
    #define HWCAP_ARM_VFPD32 HWCAP_VFPD32
#endif
#if defined(HWCAP_LPAE) && !defined(HWCAP_ARM_LPAE)
    #define HWCAP_ARM_LPAE HWCAP_LPAE
#endif
#if defined(HWCAP_EVTSTRM) && !defined(HWCAP_ARM_EVTSTRM)
    #define HWCAP_ARM_EVTSTRM HWCAP_EVTSTRM
#endif

namespace lsp
{
    typedef struct cpu_part_t
    {
        cpu_vendor_t    vendor;
        uint32_t        part;
        const char     *name;
    } cpu_part_t;

    enum cpuid_field_t {
        CPUID_UNKNOWN,
        CPUID_IMPLEMENTER,
        CPUID_ARCHITECTURE,
        CPUID_VARIANT,
        CPUID_PART,
        CPUID_REVISION
    };

    static const cpu_part_t cpu_parts[] =
    {
        // AMD
        { CPU_VENDOR_AMD, 0x000, "AMD K9 / Seattle" },

        // Ampere
        { CPU_VENDOR_AMPERE, 0xac3, "Ampere Altra / Altra Max" },
        { CPU_VENDOR_AMPERE, 0xac4, "Ampere Siryn" },

        // APM
        { CPU_VENDOR_APM, 0x000, "X-Gene Potenza" },

        // Appple
        { CPU_VENDOR_APPLE, 0x022, "Apple Icestorm" },     // M1 / A14 (Efficiency)
        { CPU_VENDOR_APPLE, 0x023, "Apple Blizzard" },     // M2 / A15 (Efficiency)
        { CPU_VENDOR_APPLE, 0x024, "Apple Sawtooth" },     // M3 / A16 (Efficiency)
        { CPU_VENDOR_APPLE, 0x025, "Apple Macaw" },        // M4 / A17 (Efficiency)
        { CPU_VENDOR_APPLE, 0x028, "Apple Firestorm" },    // M1 / A14 (Performance)
        { CPU_VENDOR_APPLE, 0x029, "Apple Firestorm-Max" },// M1 Pro/Max/Ultra
        { CPU_VENDOR_APPLE, 0x032, "Apple Avalanche" },    // M2 / A15 (Performance)
        { CPU_VENDOR_APPLE, 0x033, "Apple Avalanche-Max" },// M2 Pro/Max/Ultra
        { CPU_VENDOR_APPLE, 0x034, "Apple Everest" },      // M3 / A16 (Performance)
        { CPU_VENDOR_APPLE, 0x035, "Apple Donatello" },    // M4 / A17 (Performance)

        // ARM
        { CPU_VENDOR_ARM, 0xb02, "ARM11 MPCore" },
        { CPU_VENDOR_ARM, 0xb36, "ARM1136" },
        { CPU_VENDOR_ARM, 0xb56, "ARM1156" },
        { CPU_VENDOR_ARM, 0xb76, "ARM1176" },
        { CPU_VENDOR_ARM, 0xc05, "Cortex-A5" },
        { CPU_VENDOR_ARM, 0xc07, "Cortex-A7" },
        { CPU_VENDOR_ARM, 0xc08, "Cortex-A8" },
        { CPU_VENDOR_ARM, 0xc09, "Cortex-A9" },
        { CPU_VENDOR_ARM, 0xc0d, "Cortex-A12" },
        { CPU_VENDOR_ARM, 0xc0e, "Cortex-A17" },
        { CPU_VENDOR_ARM, 0xc0f, "Cortex-A15" },
        { CPU_VENDOR_ARM, 0xc14, "Cortex-R4" },
        { CPU_VENDOR_ARM, 0xc15, "Cortex-R5" },
        { CPU_VENDOR_ARM, 0xc17, "Cortex-R7" },
        { CPU_VENDOR_ARM, 0xc18, "Cortex-R8" },
        { CPU_VENDOR_ARM, 0xc20, "Cortex-M0" },
        { CPU_VENDOR_ARM, 0xc21, "Cortex-M1" },
        { CPU_VENDOR_ARM, 0xc23, "Cortex-M3" },
        { CPU_VENDOR_ARM, 0xc24, "Cortex-M4" },
        { CPU_VENDOR_ARM, 0xc25, "Cortex-M55" },
        { CPU_VENDOR_ARM, 0xc27, "Cortex-M7" },
        { CPU_VENDOR_ARM, 0xc28, "Cortex-M85" },
        { CPU_VENDOR_ARM, 0xc60, "Cortex-M0+" },
        { CPU_VENDOR_ARM, 0xd01, "Cortex-A32" },
        { CPU_VENDOR_ARM, 0xd02, "Cortex-A34" },
        { CPU_VENDOR_ARM, 0xd03, "Cortex-A53" },
        { CPU_VENDOR_ARM, 0xd04, "Cortex-A35" },
        { CPU_VENDOR_ARM, 0xd05, "Cortex-A55" },
        { CPU_VENDOR_ARM, 0xd06, "Cortex-A65" },
        { CPU_VENDOR_ARM, 0xd07, "Cortex-A57" },
        { CPU_VENDOR_ARM, 0xd08, "Cortex-A72" },
        { CPU_VENDOR_ARM, 0xd09, "Cortex-A73" },
        { CPU_VENDOR_ARM, 0xd0a, "Cortex-A75" },
        { CPU_VENDOR_ARM, 0xd0b, "Cortex-A76" },
        { CPU_VENDOR_ARM, 0xd0c, "Cortex-A77" },
        { CPU_VENDOR_ARM, 0xd0d, "Cortex-A78" },
        { CPU_VENDOR_ARM, 0xd0e, "Cortex-A710" },
        { CPU_VENDOR_ARM, 0xd13, "Cortex-R52" },
        { CPU_VENDOR_ARM, 0xd14, "Cortex-R82" },
        { CPU_VENDOR_ARM, 0xd20, "Cortex-M23" },
        { CPU_VENDOR_ARM, 0xd21, "Cortex-M33" },
        { CPU_VENDOR_ARM, 0xd22, "Cortex-M35P" },
        { CPU_VENDOR_ARM, 0xd23, "Cortex-M52" },
        { CPU_VENDOR_ARM, 0xd41, "Cortex-X1" },
        { CPU_VENDOR_ARM, 0xd44, "Cortex-X2" },
        { CPU_VENDOR_ARM, 0xd46, "Cortex-A510" },
        { CPU_VENDOR_ARM, 0xd4b, "Cortex-A715" },
        { CPU_VENDOR_ARM, 0xd4c, "Cortex-A720" },
        { CPU_VENDOR_ARM, 0xd4d, "Cortex-A725" },
        { CPU_VENDOR_ARM, 0xd4e, "Cortex-X3" },
        { CPU_VENDOR_ARM, 0xd4f, "Cortex-A520" },
        { CPU_VENDOR_ARM, 0xd81, "Cortex-X4" },
        { CPU_VENDOR_ARM, 0xd82, "Cortex-X925" },
        { CPU_VENDOR_ARM, 0xd83, "Cortex-A730" },
        { CPU_VENDOR_ARM, 0xd84, "Cortex-A735" },

        // Broadcom
        { CPU_VENDOR_BROADCOM, 0x0f,  "Brahma B15" },
        { CPU_VENDOR_BROADCOM, 0x100, "Brahma B53" },
        { CPU_VENDOR_BROADCOM, 0x516, "Vulcan (ThunderX2)" },

        // Cavium
        { CPU_VENDOR_CAVIUM, 0x0a1, "ThunderX" },
        { CPU_VENDOR_CAVIUM, 0x0a2, "ThunderX 81xx" },
        { CPU_VENDOR_CAVIUM, 0x0a3, "ThunderX 83xx" },
        { CPU_VENDOR_CAVIUM, 0x0af, "ThunderX2" },
        { CPU_VENDOR_CAVIUM, 0x0b8, "ThunderX3" },

        // Fujitsu
        { CPU_VENDOR_FUJITSU, 0x001, "A64FX" },

        // Marvell
        { CPU_VENDOR_MARVELL, 0x131, "Feroceon" },
        { CPU_VENDOR_MARVELL, 0x581, "PJ4 / PJ4B" },

        // NVidia
        { CPU_VENDOR_NVIDIA, 0x000, "Denver" },
        { CPU_VENDOR_NVIDIA, 0x003, "Denver 2" },
        { CPU_VENDOR_NVIDIA, 0x004, "Carmel" },
        { CPU_VENDOR_NVIDIA, 0x005, "Grace" },

        // Phytium
        { CPU_VENDOR_PHYTIUM, 0x660, "FT-1500A" },
        { CPU_VENDOR_PHYTIUM, 0x661, "FT-2000+" },
        { CPU_VENDOR_PHYTIUM, 0x662, "Tengyun S2500" },

        // Qualcomm
        { CPU_VENDOR_QUALCOMM, 0x00f, "Scorpion" },
        { CPU_VENDOR_QUALCOMM, 0x02d, "Krait" },
        { CPU_VENDOR_QUALCOMM, 0x201, "Kryo 260 / 280 Silver" },
        { CPU_VENDOR_QUALCOMM, 0x205, "Kryo 260 Gold" },
        { CPU_VENDOR_QUALCOMM, 0x211, "Kryo 280 Gold" },
        { CPU_VENDOR_QUALCOMM, 0x300, "Falkor" },
        { CPU_VENDOR_QUALCOMM, 0x800, "Kryo 360 Gold" },
        { CPU_VENDOR_QUALCOMM, 0x801, "Kryo 360 Silver" },
        { CPU_VENDOR_QUALCOMM, 0x802, "Kryo 385 Gold" },
        { CPU_VENDOR_QUALCOMM, 0x803, "Kryo 385 Silver" },
        { CPU_VENDOR_QUALCOMM, 0x804, "Kryo 485 Gold" },
        { CPU_VENDOR_QUALCOMM, 0x805, "Kryo 485 Silver" },
        { CPU_VENDOR_QUALCOMM, 0xc00, "Oryon" },                 // Snapdragon X Elite / X Plus

        // Samsung
        { CPU_VENDOR_SAMSUNG, 0x001, "Exynos M1 (Mongoose)" },
        { CPU_VENDOR_SAMSUNG, 0x002, "Exynos M2" },
        { CPU_VENDOR_SAMSUNG, 0x003, "Exynos M3" },
        { CPU_VENDOR_SAMSUNG, 0x004, "Exynos M4" },
        { CPU_VENDOR_SAMSUNG, 0x005, "Exynos M5" }
    };

    static const char * const hwcap0_list[] =
    {
        "VFPD32", "NEON",
        NULL
    };

    const char *find_cpu_name(cpu_vendor_t vendor, uint32_t part)
    {
        ssize_t first = 0, last = (sizeof(cpu_parts) / sizeof(cpu_part_t)) - 1;
        while (first <= last)
        {
            ssize_t mid         = (first + last) >> 1;
            cpu_vendor_t v      = cpu_parts[mid].vendor;
            uint32_t p          = cpu_parts[mid].part;
            if ((vendor < v) || (part < p))
                last                = mid - 1;
            else if ((vendor > v) || (part > p))
                first               = mid + 1;
            else
                return cpu_parts[mid].name;
        }
        return DEFAULT_CPU_NAME;
    }

    cpu_arch_t decode_architecture(long value)
    {
        switch (value)
        {
            case 5: return CPU_ARCH_ARM5;
            case 6: return CPU_ARCH_ARM6;
            case 7: return CPU_ARCH_ARM7;
            case 8: return CPU_ARCH_ARM8;
            case 9: return CPU_ARCH_ARM9;
            default:
                break;
        }
        return (value >= 9) ? CPU_ARCH_ARM9 : CPU_ARCH_UNKNOWN;
    }

    cpu_vendor_t decode_vendor(long value)
    {
        switch (value)
        {
            case '8':   return CPU_VENDOR_LOONGSON;
            case 'A':   return CPU_VENDOR_ARM;
            case 'B':   return CPU_VENDOR_BROADCOM;
            case 'C':   return CPU_VENDOR_CAVIUM;
            case 'D':   return CPU_VENDOR_DEC;
            case 'F':   return CPU_VENDOR_FUJITSU;
            case 'I':   return CPU_VENDOR_INFINEON;
            case 'M':   return CPU_VENDOR_MOTOROLA;
            case 'N':   return CPU_VENDOR_NVIDIA;
            case 'P':   return CPU_VENDOR_APM;
            case 'Q':   return CPU_VENDOR_QUALCOMM;
            case 'S':   return CPU_VENDOR_SAMSUNG;
            case 'T':   return CPU_VENDOR_TI;
            case 'V':   return CPU_VENDOR_MARVELL;
            case 'a':   return CPU_VENDOR_APPLE;
            case 'f':   return CPU_VENDOR_FARADAY;
            case 'i':   return CPU_VENDOR_INTEL;
            case 'p':   return CPU_VENDOR_PHYTIUM;
            case 't':   return CPU_VENDOR_TSMC;
            case 'x':   return CPU_VENDOR_AMPERE;
            case 0xc0:  return CPU_VENDOR_AMPERE;
            default:
                break;
        }
        return CPU_VENDOR_UNKNOWN;
    }

#if defined(PLATFORM_LINUX)
    static void read_cpu_info(cpuid_t * f)
    {
        // Example contents:
        // processor       : 0
        // BogoMIPS        : 38.40
        // Features        : fp asimd evtstrm crc32 cpuid
        // CPU implementer : 0x41
        // CPU architecture: 8
        // CPU variant     : 0x0
        // CPU part        : 0xd03
        // CPU revision    : 4

        // Read /proc/cpuinfo
        FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
        if (cpuinfo == NULL)
            return;  // handle error
        lsp_finally { fclose(cpuinfo); };

        size_t size = 0;
        char *line  = NULL;
        lsp_finally {
            if (line != NULL)
                free(line);
        };

        while (getline(&line, &size, cpuinfo) >= 0)
        {
            cpuid_field_t field = CPUID_UNKNOWN;
            // Find field
            if (strncasecmp(line, "CPU implementer", 15) == 0)
                field           = CPUID_IMPLEMENTER;
            else if (strncasecmp(line, "CPU architecture", 16) == 0)
                field           = CPUID_ARCHITECTURE;
            else if (strncasecmp(line, "CPU variant", 11) == 0)
                field           = CPUID_VARIANT;
            else if (strncasecmp(line, "CPU part", 8) == 0)
                field           = CPUID_PART;
            else if (strncasecmp(line, "CPU revision", 12) == 0)
                field           = CPUID_REVISION;

            if (field == CPUID_UNKNOWN) // Field not found ?
                continue;
            char *colon = strchr(line, ':'); // Colon not found ?
            if (colon++ == NULL)
                continue;

            while ((*colon) == ' ')
                colon++;
            if ((*colon) == '\0') // No data ?
                continue;

            // Detect number base
            size_t base = 10;
            if (strncasecmp(colon, "0x", 2) == 0)
            {
                colon  += 2;
                base    = 16;
            }

            // Parse value
            errno       = 0;
            long value  = strtol(colon, &colon, base);
            if (errno != 0) // Failed parse ?
                continue;
            if (((*colon) != '\0') && (*colon) != '\n') // Additional data?
                continue;

            // Store parsed value
            switch (field)
            {
                case CPUID_IMPLEMENTER:
                    f->vendor   = decode_vendor(value);
                    break;
                case CPUID_ARCHITECTURE:
                    f->arch     = decode_architecture(value);
                    break;
                case CPUID_VARIANT:
                    f->variant  = uint32_t(value);
                    break;
                case CPUID_PART:
                    f->model    = uint32_t(value);
                    break;
                case CPUID_REVISION:
                    f->revision = uint32_t(value);
                    break;
                default:
                    break;
            }
        }
    }

    static void read_cpu_name(cpuid_t *f)
    {
        const char * cpu_name = find_cpu_name(f->vendor, f->model);
        strncpy(f->name, cpu_name, sizeof(f->name));
    }

    static uint32_t read_hwcap()
    {
        uint32_t res = 0;
        unsigned long hwcap = getauxval(AT_HWCAP);
        if (hwcap & HWCAP_ARM_NEON)
            res        |= CPU_HWCAP0_NEON;
        if (hwcap & HWCAP_ARM_VFPD32)
            res        |= CPU_HWCAP0_VFPD32;

        return res;
    }
#elif defined(PLATFORM_MACOSX)
    static uint32_t read_hwcap()
    {
        int val = 0;
        size_t len = sizeof(val);
        uint32_t hwcap = 0;

        if (sysctlbyname("hw.optional.AdvSIMD", &val, &len, NULL, 0) == 0)
        {
            if (val != 0)
                hwcap          |= CPU_HWCAP0_NEON | CPU_HWCAP0_VFPD32;
        }

        val = 0;
        if (sysctlbyname("hw.optional.neon", &val, &len, NULL, 0) == 0)
        {
            if (val != 0)
                hwcap          |= CPU_HWCAP0_NEON | CPU_HWCAP0_VFPD32;
        }

        return hwcap;
    }

    static void read_cpu_name(cpuid_t *f)
    {
        size_t len = sizeof(f->name);
        sysctlbyname("machdep.cpu.brand_string", f->name, &len, nullptr, 0);
    }

    static void read_cpu_info(cpuid_t * f)
    {
        f->vendor           = CPU_VENDOR_APPLE;
    }
#elif defined(PLATFORM_FREEBSD)
    static void read_cpu_name(cpuid_t *f)
    {
        size_t len = sizeof(f->name);
        sysctlbyname("hw.model", f->name, &len, nullptr, 0);
    }

    static unsigned long read_hwcap()
    {
        unsigned long hwcap = 0;
        if (elf_aux_info(AT_HWCAP, &hwcap, sizeof(hwcap)) != 0)
            return 0;

        uint32_t res = 0;
        if (hwcap & HWCAP_ARM_NEON)
            res        |= CPU_HWCAP0_NEON;
        if (hwcap & HWCAP_ARM_VFPD32)
            res        |= CPU_HWCAP0_VFPD32;

        return res;
    }

    static void read_cpu_info(cpuid_t * f)
    {
        uint32_t vendor = 0;
        uint32_t part = 0;
        size_t len = sizeof(uint32_t);

        // Read vendor (implementor)
        if (sysctlbyname("hw.id.implementor", &vendor, &len, nullptr, 0) == 0)
            f->vendor       = decode_vendor(vendor);

        // Read cpu part
        len = sizeof(uint32_t);
        if (sysctlbyname("hw.id.part", &part, &len, nullptr, 0) == 0)
            f->model        = part;
    }
#else
    static void read_cpu_name(cpuid_t *f)
    {
        strncpy(f->name, DEFAULT_CPU_NAME, sizeof(f->name));
    }

    static unsigned long read_hwcap()
    {
        return 0;
    }

    static void read_cpu_info(cpuid_t * f)
    {
    }
#endif /* PLATFORM_FREEBSD */

    static void cpuid_impl(cpuid_t * f)  // must be at least 13 bytes
    {
        f->vendor               = CPU_VENDOR_UNKNOWN;
        f->arch                 = CPU_ARCH_UNKNOWN;
        f->micro                = CPU_MICRO_UNKNOWN;
        IF_ARCH_ARM6(f->arch    = CPU_ARCH_ARM6);
        IF_ARCH_ARM7(f->arch    = CPU_ARCH_ARM7);
        IF_ARCH_ARM8(f->arch    = CPU_ARCH_ARM8);
        f->variant              = 0;
        f->model                = 0;
        f->revision             = 0;
        strncpy(f->name, DEFAULT_CPU_NAME, sizeof(f->name));

        f->hwcap[0]             = read_hwcap();
        read_cpu_info(f);
        read_cpu_name(f);

        f->name[sizeof(f->name) - 1] = '\0';
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
            "vendor=0x%x, part=0x%x",
            int(features->vendor), int(features->model));
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

#endif /* PRIVATE_ARCH_ARM_CPUID_H_ */
