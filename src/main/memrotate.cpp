/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 13 июл. 2026 г.
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

#include <lsp-plug.in/stdlib/string.h>

namespace lsp
{
    void memrotate(void *ptr, size_t length, size_t count)
    {
        // Check size
        if (length == 0)
            return;
        count %= length;
        if (count == 0)
            return;

        size_t na   = count;
        size_t nb   = length - count;
        uint8_t *a  = static_cast<uint8_t *>(ptr);
        uint8_t *b  = &a[na];

        // Apply rotation
        while (na != nb)
        {
            if (na > nb)
            {
                memswap(a, b, nb);
                a  += nb;
                na -= nb;
            }
            else
            {
                memswap(a, &b[nb-na], na);
                nb -= na;
            }
        }

        if (na > 0)
            memswap(a, b, na);
    }
} /* namespace lsp */


