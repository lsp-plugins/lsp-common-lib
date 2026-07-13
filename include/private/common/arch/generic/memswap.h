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

#ifndef PRIVATE_COMMON_ARCH_GENERIC_MEMSWAP_H_
#define PRIVATE_COMMON_ARCH_GENERIC_MEMSWAP_H_

#ifndef PRIVATE_COMMON_ARCH_GENERIC_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_COMMON_ARCH_GENERIC_IMPL */

namespace lsp
{
    namespace generic
    {
        void memswap(void *a, void *b, size_t count)
        {
            // We use small block sizes to make compiler inline the memcpy() call
            constexpr size_t block_size = 32;
            uint8_t block[block_size];

            while (count >= block_size)
            {
                memcpy(block, a, block_size);
                a = mempcpy(a, b, block_size);
                b = mempcpy(b, block, block_size);
                count -= block_size;
            }
            if (count > 0)
            {
                memcpy(block, a, count);
                memcpy(a, b, count);
                memcpy(b, block, count);
            }
        }
    } /* namespace generic */
} /* namespace lsp */


#endif /* PRIVATE_COMMON_ARCH_GENERIC_MEMSWAP_H_ */
