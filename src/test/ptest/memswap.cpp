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

#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/test-fw/ptest.h>

#define MIN_RANK 4
#define MAX_RANK 16

namespace lsp
{
    namespace generic
    {
        void memswap(void *a, void *b, size_t count);
    }

    IF_ARCH_X86(
        namespace x86
        {
            void memswap(void *a, void *b, size_t count);
        }

        namespace sse
        {
            void memswap(void *a, void *b, size_t count);
        }

        namespace avx
        {
            void memswap(void *a, void *b, size_t count);
        }

        namespace avx512
        {
            void memswap(void *a, void *b, size_t count);
        }
    )

//    IF_ARCH_ARM(
//        namespace arm
//        {
//            void memswap(void *a, void *b, size_t count);
//        }

//        namespace neon_d32
//        {
//            void memswap(void *a, void *b, size_t count);
//        }
//    )

//    IF_ARCH_AARCH64(
//        namespace aarch64
//        {
//            void memswap(void *a, void *b, size_t count);
//        }

//        namespace asimd
//        {
//            void memswap(void *a, void *b, size_t count);
//        }
//    )
}

//-----------------------------------------------------------------------------
// Performance test
PTEST_BEGIN("common", memswap, 2, 1000)

    void call(const char *label, uint8_t *a, uint8_t *b, size_t count, memswap_t func)
    {
        if (!PTEST_SUPPORTED(func))
            return;

        char buf[80];
        snprintf(buf, sizeof(buf), "%s x %d", label, int(count));
        printf("Testing %s bytes...\n", buf);

        PTEST_LOOP(buf,
            func(a, b, count);
        );
    }

    PTEST_MAIN
    {
        size_t buf_size = 1 << MAX_RANK;
        uint8_t *data   = NULL;
        uint8_t *a      = alloc_aligned<uint8_t>(data, buf_size * 2, 64);
        uint8_t *b      = &a[buf_size];

        for (size_t i=0; i < buf_size*2; ++i)
            a[i]            = uint8_t(i);

        #define CALL(func) \
            call(#func, a, b, count, func);

        for (size_t i=MIN_RANK; i <= MAX_RANK; ++i)
        {
            size_t count = 1 << i;

            CALL(generic::memswap);
            IF_ARCH_X86(CALL(x86::memswap));
            IF_ARCH_X86(CALL(sse::memswap));
            IF_ARCH_X86(CALL(avx::memswap));
            IF_ARCH_X86(CALL(avx512::memswap));
//            IF_ARCH_ARM(CALL(neon_d32::memswap));
//            IF_ARCH_AARCH64(CALL(asimd::memswap));
            PTEST_SEPARATOR;

        }

        free_aligned(data);
    }
PTEST_END

