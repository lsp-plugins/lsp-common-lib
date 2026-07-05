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

#include <lsp-plug.in/common/cpuid.h>
#include <lsp-plug.in/test-fw/utest.h>

UTEST_BEGIN("common", cpuid)

    UTEST_MAIN
    {
        lsp::cpuid_t id;
        lsp::cpuid(&id);

        lsp::cpuinfo_t * const sinfo = lsp::cpuinfo(&id);
        UTEST_ASSERT(sinfo != NULL);
        lsp_finally { free(sinfo); };

        printf("CPUID information:\n");
        printf("  Vendor:               %s (0x%x)\n", sinfo->vendor, int(id.vendor));
        printf("  Architecture:         %s (0x%x)\n", sinfo->arch, int(id.arch));
        printf("  Microarchitecture:    %s (0x%x)\n", sinfo->micro, int(id.micro));
        printf("  Model:                0x%x\n", int(id.model));
        printf("  Variant:              0x%x\n", int(id.variant));
        printf("  Revision:             0x%x\n", int(id.revision));
        printf("  Model string:         %s\n", sinfo->model);
        printf("  Capability bitmask:   0x%x 0x%x\n", int(id.hwcap[0]), int(id.hwcap[1]));
        printf("  Capability features:  %s\n", sinfo->features);
    }

UTEST_END;




