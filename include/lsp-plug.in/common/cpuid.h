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

#ifndef LSP_PLUG_IN_COMMON_CPUID_H_
#define LSP_PLUG_IN_COMMON_CPUID_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

#if defined(ARCH_I386) || defined(ARCH_X86_64)
    #include <lsp-plug.in/common/arch/x86/hwcap.h>
#elif defined(ARCH_AARCH64)
    #include <lsp-plug.in/common/arch/aarch64/hwcap.h>
#elif defined(ARCH_ARM)
    #include <lsp-plug.in/common/arch/arm/hwcap.h>
#else
    #include <lsp-plug.in/common/arch/generic/hwcap.h>
#endif

namespace lsp
{
    enum cpu_vendor_t
    {
        CPU_VENDOR_UNKNOWN,

        CPU_VENDOR_AMD,
        CPU_VENDOR_AMPERE,
        CPU_VENDOR_APM,
        CPU_VENDOR_APPLE,
        CPU_VENDOR_ARM,
        CPU_VENDOR_BROADCOM,
        CPU_VENDOR_CAVIUM,
        CPU_VENDOR_CYRIX,
        CPU_VENDOR_DEC,
        CPU_VENDOR_DMP_ELECTRONICS,
        CPU_VENDOR_FARADAY,
        CPU_VENDOR_FUJITSU,
        CPU_VENDOR_HYGON,
        CPU_VENDOR_INFINEON,
        CPU_VENDOR_INTEL,
        CPU_VENDOR_LOONGSON,
        CPU_VENDOR_MARVELL,
        CPU_VENDOR_MCST,
        CPU_VENDOR_MICROSOFT,
        CPU_VENDOR_MOTOROLA,
        CPU_VENDOR_NEXGEN,
        CPU_VENDOR_NSC,
        CPU_VENDOR_NVIDIA,
        CPU_VENDOR_PHYTIUM,
        CPU_VENDOR_QUALCOMM,
        CPU_VENDOR_RDCS,
        CPU_VENDOR_RISE,
        CPU_VENDOR_SAMSUNG,
        CPU_VENDOR_SIS,
        CPU_VENDOR_TI,
        CPU_VENDOR_TRANSMETA,
        CPU_VENDOR_TSMC,
        CPU_VENDOR_UMC,
        CPU_VENDOR_VIA,
        CPU_VENDOR_ZHAOXIN,
    };

    enum cpu_arch_t
    {
        CPU_ARCH_UNKNOWN,

        CPU_ARCH_I386,
        CPU_ARCH_I486,
        CPU_ARCH_I586,
        CPU_ARCH_I686,
        CPU_ARCH_X86_64,

        CPU_ARCH_ARM5,
        CPU_ARCH_ARM6,
        CPU_ARCH_ARM7,
        CPU_ARCH_ARM8,
        CPU_ARCH_ARM9,

        CPU_ARCH_RISCV32,
        CPU_ARCH_RISCV64,
        CPU_ARCH_RISCV128,

        CPU_ARCH_LOONGARCH32,
        CPU_ARCH_LOONGARCH64,

        CPU_ARCH_PPC,
        CPU_ARCH_PPC64,

        CPU_ARCH_MIPS32,
        CPU_ARCH_MIPS64,

        CPU_ARCH_S390,
        CPU_ARCH_SPARC,

    #if defined(ARCH_X86_64)
        CPU_ARCH_CURRENT    = CPU_ARCH_X86_64,
    #elif defined(ARCH_I386)
        CPU_ARCH_CURRENT    = CPU_ARCH_I686,
    #elif defined(ARCH_ARM8)
        CPU_ARCH_CURRENT    = CPU_ARCH_ARM8,
    #elif defined(ARCH_ARM7)
        CPU_ARCH_CURRENT    = CPU_ARCH_ARM7,
    #elif defined(ARCH_ARM6)
        CPU_ARCH_CURRENT    = CPU_ARCH_ARM6,
    #elif defined(ARCH_PPC64)
        CPU_ARCH_CURRENT    = CPU_ARCH_PPC64,
    #elif defined(ARCH_PPC)
        CPU_ARCH_CURRENT    = CPU_ARCH_PPC,
    #elif defined(ARCH_S390)
        CPU_ARCH_CURRENT    = CPU_ARCH_S390,
    #elif defined(ARCH_MIPS32)
        CPU_ARCH_CURRENT    = CPU_ARCH_MIPS32,
    #elif defined(ARCH_MIPS64)
        CPU_ARCH_CURRENT    = CPU_ARCH_MIPS64,
    #elif defined(ARCH_SPARC)
        CPU_ARCH_CURRENT    = SPARC,
    #elif defined(ARCH_RISCV64)
        CPU_ARCH_CURRENT    = CPU_ARCH_RISCV64,
    #elif defined(ARCH_RISCV64)
        CPU_ARCH_CURRENT    = CPU_ARCH_RISCV32,
    #elif defined(ARCH_LOONGARCH32)
        CPU_ARCH_CURRENT    = CPU_ARCH_LOONGARCH32,
    #elif defined(ARCH_LOONGARCH64)
        CPU_ARCH_CURRENT    = CPU_ARCH_LOONGARCH32,
    #else
        CPU_ARCH_CURRENT    = CPU_ARCH_UKNNOWN,
    #endif
    };

    enum cpu_micro_t
    {
        CPU_MICRO_UNKNOWN,

        CPU_MICRO_AMD_K8_HAMMER,
        CPU_MICRO_AMD_K10,
        CPU_MICRO_AMD_K10_GRIFFIN,
        CPU_MICRO_AMD_K10_LLANO,
        CPU_MICRO_AMD_BOBCAT,
        CPU_MICRO_AMD_BULLDOZER,
        CPU_MICRO_AMD_PILEDRIVER,
        CPU_MICRO_AMD_STEAMROLLER,
        CPU_MICRO_AMD_EXCAVATOR,
        CPU_MICRO_AMD_JAGUAR,
        CPU_MICRO_AMD_PUMA,
        CPU_MICRO_AMD_ZEN1,
        CPU_MICRO_AMD_ZEN_PLUS,
        CPU_MICRO_AMD_ZEN2,
        CPU_MICRO_AMD_DHYANA,
        CPU_MICRO_AMD_ZEN3,
        CPU_MICRO_AMD_ZEN4,
        CPU_MICRO_AMD_ZEN5,

        CPU_MICRO_INTEL_NEHALEM,
        CPU_MICRO_INTEL_WESTMERE,
        CPU_MICRO_INTEL_SANDY_BRIDGE,
        CPU_MICRO_INTEL_IVY_BRIDGE,
        CPU_MICRO_INTEL_HASWELL,
        CPU_MICRO_INTEL_SILVERMONT,
        CPU_MICRO_INTEL_AIRMONT,
        CPU_MICRO_INTEL_BROADWELL,
        CPU_MICRO_INTEL_SKYLAKE,
        CPU_MICRO_INTEL_GOLDMONT,
        CPU_MICRO_INTEL_KABY_LAKE,
        CPU_MICRO_INTEL_COFFEE_LAKE         = CPU_MICRO_INTEL_KABY_LAKE,
        CPU_MICRO_INTEL_COMET_LAKE          = CPU_MICRO_INTEL_KABY_LAKE,
        CPU_MICRO_INTEL_GOLDMONT_PLUS,
        CPU_MICRO_INTEL_GEMINI_LAKE         = CPU_MICRO_INTEL_GOLDMONT_PLUS,
        CPU_MICRO_INTEL_ICE_LAKE,
        CPU_MICRO_INTEL_TREMONT,
        CPU_MICRO_INTEL_JASPER_LAKE,
        CPU_MICRO_INTEL_TIGER_LAKE,
        CPU_MICRO_INTEL_ROCKET_LAKE,
        CPU_MICRO_INTEL_ALDER_LAKE,
        CPU_MICRO_INTEL_RAPTOR_LAKE,
        CPU_MICRO_INTEL_ALDER_LAKE_N,
        CPU_MICRO_INTEL_METEOR_LAKE,
        CPU_MICRO_INTEL_LUNAR_LAKE,
        CPU_MICRO_INTEL_ARROW_LAKE          = CPU_MICRO_INTEL_LUNAR_LAKE,
        CPU_MICRO_INTEL_PANTHER_LAKE,
    };

    typedef struct cpuid_t
    {
        /**
         * CPU vendor/implementer.
         */
        cpu_vendor_t    vendor;

        /**
         * Architecture identifier.
         */
        cpu_arch_t      arch;

        /**
         * CPU microarchitecture identifier.
         */
        cpu_micro_t     micro;

        /**
         * CPU model/part number
         */
        uint32_t        model;

        /**
         * CPU variant number
         */
        uint32_t        variant;

        /**
         * CPU Revision number
         */
        uint32_t        revision;

        /**
         * Array of hardware compatibilities
         */
        uint32_t        hwcap[2];

        /**
         * The name of the CPU.
         */
        char            name[128];
    } cpuid_t;

    /**
     * CPU information
     */
    typedef struct cpuinfo_t
    {
        /**
         * Vendor sring
         */
        const char     *vendor;

        /**
         * Architecture string
         */
        const char     *arch;

        /**
         * Microarchitecture string
         */
        const char     *micro;

        /**
         * CPU name
         */
        const char     *name;

        /**
         * CPU model details
         */
        const char     *model;

        /**
         * CPU features
         */
        const char     *features;
    } cpuinfo_t;

    /**
     * Identify processor features as a plain data structure.
     * The result is cached to improve performance on multiple sequential calls.
     * @param features pointer to store processor features.
     * @param force force flag. Updates the cache if set to true.
     */
    void            cpuid(cpuid_t *features, bool force = false);

    /**
     * Decode processor features as a set of strings.
     * The resulting data is allocated on heap, caller is responsible
     * to call free() on the pointer.
     *
     * @param features pointer to read processor features.
     * @return
     */
    cpuinfo_t      *cpuinfo(const cpuid_t *features);

    /**
     * Get the CPU vendor name string
     * @param vendor vendor identifier
     * @return pointer to vendor name string
     */
    const char     *cpu_vendor(cpu_vendor_t vendor);

    /**
     * Get the CPU architecture name string
     * @param arch CPU architecture
     * @return pointer to architecture name string
     */
    const char     *cpu_arch(cpu_arch_t arch);

    /**
     * Get the CPU micro-architecture name string
     * @param micro CPU micro-architecture
     * @return pointer to micro architecture name string
     */
    const char     *cpu_micro(cpu_micro_t micro);

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_CPUID_H_ */
