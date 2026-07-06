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

#ifndef LSP_PLUG_IN_COMMON_ARCH_ARM_HWCAP_H_
#define LSP_PLUG_IN_COMMON_ARCH_ARM_HWCAP_H_

namespace lsp
{
    enum cpu_hwcap0_t
    {
        // Different feature set
        CPU_HWCAP0_NEON             = 1 << 0,
        CPU_HWCAP0_VFPD32           = 1 << 1
    };

} /* namespace lsp */


#endif /* LSP_PLUG_IN_COMMON_ARCH_ARM_HWCAP_H_ */
