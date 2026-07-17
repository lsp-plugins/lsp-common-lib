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
    constexpr size_t BLOCK_SIZE = 8;

    static size_t symmerge_binary_search(
        uint8_t *u, size_t u_len, uint8_t *v, size_t v_len,
        size_t szof, sort_compar_r_t compar, void *arg)
    {
        size_t low          = 0;
        size_t high         = lsp_min(u_len, v_len);
        const size_t u_end  = (u_len - 1)*szof;

        while (low < high)
        {
            const size_t mid        = low + ((high - low) >> 1);
            const size_t mid_off    = mid * szof;
            uint8_t * const u_elem  = &u[u_end - mid_off];
            uint8_t * const v_elem  = &v[mid_off];

            if (compar(u_elem, v_elem, arg) > 0)
                low                     = mid + 1;
            else
                high                    = mid;
        }
        return low;
    }

    static size_t symmerge_binary_search(
        uint8_t *u, size_t u_len, uint8_t *v, size_t v_len,
        size_t szof, sort_compar_t compar)
    {
        size_t low          = 0;
        size_t high         = lsp_min(u_len, v_len);
        const size_t u_end  = (u_len - 1)*szof;

        while (low < high)
        {
            const size_t mid        = low + ((high - low) >> 1);
            const size_t mid_off    = mid * szof;
            uint8_t * const u_elem  = &u[u_end - mid_off];
            uint8_t * const v_elem  = &v[mid_off];

            if (compar(u_elem, v_elem) > 0)
                low                     = mid + 1;
            else
                high                    = mid;
        }
        return low;
    }

    static void symmerge(uint8_t *first, uint8_t *mid, uint8_t *last, size_t szof, sort_compar_r_t compar, void *arg)
    {
        const size_t u_len = (mid - first) / szof;
        const size_t v_len = (last - mid) / szof;

        // Basic cases
        if ((u_len == 0) || (v_len == 0))
            return;

        if ((u_len == 1) && (v_len == 1))
        {
            if (compar(mid, first, arg) < 0)
                memswap(first, mid, szof);
            return;
        }

        // Find number elements for exchange
        const size_t k = symmerge_binary_search(first, u_len, mid, v_len, szof, compar, arg);
        const size_t u_size = u_len * szof;
        const size_t blk_size = k * szof;
        uint8_t * const split = &first[u_size - blk_size];
        if (k > 0)
            memswap(split, &split[blk_size], blk_size);

        // Perform recursive call
        uint8_t * const new_mid = &first[u_size];
        symmerge(first, split, new_mid, szof, compar, arg);
        symmerge(new_mid, &new_mid[blk_size], last, szof, compar, arg);
    }

    static void symmerge(uint8_t *first, uint8_t *mid, uint8_t *last, size_t szof, sort_compar_t compar)
    {
        const size_t u_len = (mid - first) / szof;
        const size_t v_len = (last - mid) / szof;

        // Basic cases
        if ((u_len == 0) || (v_len == 0))
            return;

        if ((u_len == 1) && (v_len == 1))
        {
            if (compar(mid, first) < 0)
                memswap(first, mid, szof);
            return;
        }

        // Find number elements for exchange
        const size_t k = symmerge_binary_search(first, u_len, mid, v_len, szof, compar);
        const size_t u_size = u_len * szof;
        const size_t blk_size = k * szof;
        uint8_t * const split = &first[u_size - blk_size];
        if (k > 0)
            memswap(split, &split[blk_size], blk_size);

        // Perform recursive call
        uint8_t * const new_mid = &first[u_size];
        symmerge(first, split, new_mid, szof, compar);
        symmerge(new_mid, &new_mid[blk_size], last, szof, compar);
    }

    static void insertion_sort(uint8_t *head, size_t count, size_t szof, sort_compar_r_t compar, void *arg)
    {
        for (size_t i = 1; i < count; ++i)
        {
            uint8_t *curr = &head[i * szof];
            while ((curr > head) && (compar(curr, curr - szof, arg) < 0))
            {
                memswap(curr, curr - szof, szof);
                curr -= szof;
            }
        }
    }

    static void insertion_sort(uint8_t *head, size_t count, size_t szof, sort_compar_t compar)
    {
        for (size_t i = 1; i < count; ++i)
        {
            uint8_t *curr = &head[i * szof];
            while ((curr > head) && (compar(curr, curr - szof) < 0))
            {
                memswap(curr, curr - szof, szof);
                curr -= szof;
            }
        }
    }

    LSP_COMMON_LIB_PUBLIC
    void ssort_r(void *data, size_t count, size_t szof, sort_compar_r_t compar, void *arg)
    {
        if (count < 2)
            return;

        uint8_t * const base = static_cast<uint8_t *>(data);
        uint8_t * const end  = &base[count * szof];

        // Step 1: sort small blocks using insertion sort.
        uint8_t * iptr  = base;
        size_t szof_blk = BLOCK_SIZE * szof;
        for (size_t start = 0; start < count; start += BLOCK_SIZE)
        {
            const size_t blk_size   = lsp_min(BLOCK_SIZE, count - start);
            insertion_sort(iptr, blk_size, szof, compar, arg);
            iptr += szof_blk;
        }

        // Step 2: perform symmerge
        for (size_t i = BLOCK_SIZE; i < count; i <<= 1, szof_blk <<= 1)
        {
            const size_t szof_blk2 = szof_blk << 1;

            for (uint8_t *head = base; head < end; head += szof_blk2)
            {
                uint8_t * const mid = &head[szof_blk];
                if (mid >= end)
                    break;

                uint8_t * const right_end = lsp_min(&head[szof_blk2], end);
                symmerge(head, mid, right_end, szof, compar, arg);
            }
        }
    }

    LSP_COMMON_LIB_PUBLIC
    void ssort(void *data, size_t count, size_t szof, sort_compar_t compar)
    {
        if (count < 2)
            return;

        uint8_t * const base = static_cast<uint8_t *>(data);
        uint8_t * const end  = &base[count * szof];

        // Step 1: sort small blocks using insertion sort.
        uint8_t * iptr  = base;
        size_t szof_blk = BLOCK_SIZE * szof;
        for (size_t start = 0; start < count; start += BLOCK_SIZE)
        {
            const size_t blk_size   = lsp_min(BLOCK_SIZE, count - start);
            insertion_sort(iptr, blk_size, szof, compar);
            iptr += szof_blk;
        }

        // Step 2: perform symmerge
        for (size_t i = BLOCK_SIZE; i < count; i <<= 1, szof_blk <<= 1)
        {
            const size_t szof_blk2 = szof_blk << 1;

            for (uint8_t *head = base; head < end; head += szof_blk2)
            {
                uint8_t * const mid = &head[szof_blk];
                if (mid >= end)
                    break;

                uint8_t * const right_end = lsp_min(&head[szof_blk2], end);
                symmerge(head, mid, right_end, szof, compar);
            }
        }
    }

} /* namespace lsp */


