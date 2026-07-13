/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 24 мая 2026 г.
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

#include <lsp-plug.in/stdlib/stdlib.h>
#include <lsp-plug.in/stdlib/string.h>

namespace lsp
{
    constexpr size_t block_size = 0x1000;

    static inline void memswap(uint8_t *a, uint8_t *b, size_t count)
    {
        uint8_t block[block_size];
        for (size_t offset = 0; offset < count; )
        {
            const size_t to_do  = lsp_min(count - offset, block_size);
            memcpy(block, a, to_do);
            memcpy(a, b, to_do);
            memcpy(b, block, to_do);

            offset += to_do;
        }
    }

    static void memreverse(uint8_t *data, size_t count)
    {
        uint8_t *last = &data[count];
        while (data < --last)
        {
            const uint8_t tmp   = *data;
            *(data++)           = *last;
            *last               = tmp;
        }
    }

    static void memrotate(uint8_t *a, size_t length, size_t count)
    {
        if ((count == 0) || (count == length))
            return;

        memreverse(a, count);
        memreverse(&a[count], length - count);
        memreverse(a, length);
    }

    static void merge(uint8_t *a, uint8_t *b, uint8_t *end, size_t szof, sort_compar_t compar, void *arg)
    {
        while ((a < b) && (b < end))
        {
            // Skip all first a's that are not greater than first b
            while (compar(a, b, arg) <= 0)
            {
                // All a's have been skipped?
                a      += szof;
                if (a >= b)
                    return;
            }

            // Now count all b's less than current a
            uint8_t * const old_b   = b;
            while (compar(a, b, arg) > 0)
            {
                b      += szof;
                if (b >= end)
                    break;
            }

            // Place all b's before current a
            const ptrdiff_t count   = b - a;
            const ptrdiff_t diff    = b - old_b;
            memrotate(a, count, count - diff);

            // Update current position of a
            a                      += diff;
        }
    }

    LSP_COMMON_LIB_PUBLIC
    void ssort_r(void *data, size_t count, size_t szof, sort_compar_t compar, void *arg)
    {
        // Step 1: split code into pairs and sort items within pairs
        if (count < 2)
            return;

        uint8_t *head = static_cast<uint8_t *>(data);
        uint8_t * const end = &head[count * szof];

        size_t szof_blk = szof << 1;
        for (size_t i=0, n=count >> 1; i<n; ++i)
        {
            if (compar(&head[szof], &head[0], arg) < 0)
                memswap(&head[szof], &head[0], szof);
            head += szof_blk;
        }

        // Step 2: merge neighbour blocks together
        for (size_t i=2; i<count; i <<= 1, szof_blk <<= 1)
        {
            const size_t szof_blk2 = szof_blk << 1;
            for (head = static_cast<uint8_t *>(data); head < end; head += szof_blk2)
                merge(head, &head[szof_blk], lsp_min(&head[szof_blk2], end), szof, compar, arg);
        }
    }

} /* namespace lsp */


