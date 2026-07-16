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

#ifndef PRIVATE_ARCH_GENERIC_CPUID_H_
#define PRIVATE_ARCH_GENERIC_CPUID_H_

#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/alloc.h>

#define DEFAULT_CPU_NAME        "Generic processor"

namespace lsp
{

    static void cpuid_impl(cpuid_t * f)  // must be at least 13 bytes
    {
        f->vendor               = CPU_VENDOR_UNKNOWN;
        f->arch                 = CPU_ARCH_UNKNOWN;
        f->micro                = CPU_MICRO_UNKNOWN;
        f->variant              = 0;
        f->model                = 0;
        f->revision             = 0;
        strncpy(f->name, DEFAULT_CPU_NAME, sizeof(f->name));

        f->hwcap[0]             = 0;
    }

    cpuinfo_t *cpuinfo(const cpuid_t *features)
    {
        const char *vendor  = cpu_vendor(features->vendor);
        const char *arch    = cpu_arch(features->arch);
        const char *micro   = cpu_micro(features->micro);

        const size_t szof   = sizeof(cpuinfo_t);

        cpuinfo_t * const res   = malloc_bytes<cpuinfo_t>(szof);
        if (res == NULL)
            return res;

        res->vendor         = vendor;
        res->arch           = arch;
        res->micro          = micro;
        res->name           = DEFAULT_CPU_NAME;
        res->model          = "";
        res->features       = "";

        return res;
    }

} /* namespace lsp  */


#endif /* PRIVATE_ARCH_GENERIC_CPUID_H_ */
