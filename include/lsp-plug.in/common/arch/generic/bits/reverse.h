/*
 * Copyright (C) 2023 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2023 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 5 мар. 2023 г.
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

#ifndef LSP_PLUG_IN_COMMON_ARCH_GENERIC_BITS_REVERSE_H_
#define LSP_PLUG_IN_COMMON_ARCH_GENERIC_BITS_REVERSE_H_

#ifndef LSP_PLUG_IN_COMMON_BITS_IMPL
    #error "This file should not be included directly"
#endif /* LSP_PLUG_IN_COMMON_BITS_IMPL */

namespace lsp
{
    // Unsigned implementation
    inline uint8_t      reverse_bits(uint8_t src)
    {
        return lsp_rb_data[src];
    }

    inline uint16_t     reverse_bits(uint16_t v)
    {
        return (uint16_t(lsp_rb_data[v & 0xff]) << 8) | (uint16_t(lsp_rb_data[v >> 8]));
    }

    inline uint32_t     reverse_bits(uint32_t v)
    {
        return
            (uint32_t(lsp_rb_data[v >> 24])) |
            (uint32_t(lsp_rb_data[(v >> 16) & 0xff]) << 8) |
            (uint32_t(lsp_rb_data[(v >> 8) & 0xff]) << 16) |
            (uint32_t(lsp_rb_data[v & 0xff]) << 24);
    }

    inline uint64_t     reverse_bits(uint64_t v)
    {
        return
            (uint64_t(lsp_rb_data[v >> 56])) |
            (uint64_t(lsp_rb_data[(v >> 48) & 0xff]) << 8) |
            (uint64_t(lsp_rb_data[(v >> 40) & 0xff]) << 16) |
            (uint64_t(lsp_rb_data[(v >> 32) & 0xff]) << 24) |
            (uint64_t(lsp_rb_data[(v >> 24) & 0xff]) << 32) |
            (uint64_t(lsp_rb_data[(v >> 16) & 0xff]) << 40) |
            (uint64_t(lsp_rb_data[(v >> 8) & 0xff]) << 48) |
            (uint64_t(lsp_rb_data[v & 0xff]) << 56);
    }

    inline uint8_t      reverse_bits(uint8_t v, size_t count)
    {
        return reverse_bits(v) >> (sizeof(uint8_t) * 8 - count);
    }

    inline uint16_t     reverse_bits(uint16_t v, size_t count)
    {
        return reverse_bits(v) >> (sizeof(uint16_t) * 8 - count);
    }

    inline uint32_t     reverse_bits(uint32_t v, size_t count)
    {
        return reverse_bits(v) >> (sizeof(uint32_t) * 8 - count);
    }

    inline uint64_t     reverse_bits(uint64_t v, size_t count)
    {
        return reverse_bits(v) >> (sizeof(uint64_t) * 8 - count);
    }

    // Signed implementation
    inline int8_t __lsp_forced_inline      reverse_bits(int8_t v)
    {
        return reverse_bits(uint8_t(v));
    }

    inline int16_t __lsp_forced_inline     reverse_bits(int16_t v)
    {
        return reverse_bits(uint16_t(v));
    }

    inline int32_t __lsp_forced_inline     reverse_bits(int32_t v)
    {
        return reverse_bits(uint32_t(v));
    }

    inline int64_t __lsp_forced_inline     reverse_bits(int64_t v)
    {
        return reverse_bits(uint64_t(v));
    }

    inline int8_t __lsp_forced_inline      reverse_bits(int8_t v, size_t count)
    {
        return reverse_bits(uint8_t(v), count);
    }

    inline int16_t __lsp_forced_inline     reverse_bits(int16_t v, size_t count)
    {
        return reverse_bits(uint16_t(v), count);
    }

    inline int32_t __lsp_forced_inline     reverse_bits(int32_t v, size_t count)
    {
        return reverse_bits(uint32_t(v), count);
    }

    inline int64_t __lsp_forced_inline     reverse_bits(int64_t v, size_t count)
    {
        return reverse_bits(uint64_t(v), count);
    }
} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_ARCH_GENERIC_BITS_REVERSE_H_ */
