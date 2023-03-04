/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 1 апр. 2020 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_GENERIC_INT_LOG2_H_
#define LSP_PLUG_IN_COMMON_ARCH_GENERIC_INT_LOG2_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    inline int __lsp_forced_inline     int_log2(uint8_t v)
    {
        int res = 0;
        if (v & 0xf0) { res += 4; v >>= 4; }
        if (v & 0x0c) { res += 2; v >>= 2; }
        if (v & 0x02) ++res;
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint16_t v)
    {
        int res = 0;
        if (v & 0xff00) { res += 8; v >>= 8; }
        if (v & 0xf0) { res += 4; v >>= 4; }
        if (v & 0x0c) { res += 2; v >>= 2; }
        if (v & 0x02) ++res;
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint32_t v)
    {
        int res = 0;
        if (v & 0xffff0000) { res += 16; v >>= 16; }
        if (v & 0xff00) { res += 8; v >>= 8; }
        if (v & 0xf0) { res += 4; v >>= 4; }
        if (v & 0x0c) { res += 2; v >>= 2; }
        if (v & 0x02) ++res;
        return res;
    }

    inline int __lsp_forced_inline     int_log2(uint64_t v)
    {
        int res = 0;
        if (v & 0xffffffff00000000ULL) { res += 32; v >>= 32; }
        if (v & 0xffff0000) { res += 16; v >>= 16; }
        if (v & 0xff00) { res += 8; v >>= 8; }
        if (v & 0xf0) { res += 4; v >>= 4; }
        if (v & 0x0c) { res += 2; v >>= 2; }
        if (v & 0x02) ++res;
        return res;
    }

    inline int __lsp_forced_inline     int_log2(int8_t v)
    {
        return int_log2(uint8_t(v));
    }

    inline int __lsp_forced_inline     int_log2(int16_t v)
    {
        return int_log2(uint16_t(v));
    }

    inline int __lsp_forced_inline     int_log2(int32_t v)
    {
        return int_log2(uint32_t(v));
    }

    inline int __lsp_forced_inline     int_log2(int64_t v)
    {
        return int_log2(uint64_t(v));
    }

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_GENERIC_INT_LOG2_H_ */
