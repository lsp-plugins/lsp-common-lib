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

#include <lsp-plug.in/common/singletone.h>
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/test-fw/ByteBuffer.h>

UTEST_BEGIN("common", memrotate)


    UTEST_MAIN
    {
        UTEST_FOREACH(count,
            /*0, 1, 2, 3, */ 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 63, 64)
        {
            printf("Testing memrotate on input buffer of %d bytes...\n", int(count));

            for (size_t shift = 0; shift <= count; ++shift)
            {
                ByteBuffer src(count);
                ByteBuffer cmp(count);
                for (size_t i=0; i<count; ++i)
                {
                    src[i] = uint8_t(i);
                    cmp[i] = uint8_t((i + shift) % count);
                }
                ByteBuffer buf(src);

                memrotate(buf, count, shift);

                UTEST_ASSERT_MSG(buf.valid(), "Buffer buf corrupted");

                // Compare buffers
                if (!buf.equals(cmp))
                {
                    src.dump("src");
                    buf.dump("buf");
                    cmp.dump("cmp");

                    UTEST_FAIL_MSG("Output of functions for differs for shift=%d", int(shift));
                }
            }
        }
    }
UTEST_END;


