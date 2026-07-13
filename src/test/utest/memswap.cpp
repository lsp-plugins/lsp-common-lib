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
#include <lsp-plug.in/stdlib/string.h>
#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/test-fw/ByteBuffer.h>

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
// Unit test for complex multiplication
UTEST_BEGIN("common", memswap)

    void call(const char *label, size_t align, memswap_t func)
    {
        if (!UTEST_SUPPORTED(func))
            return;

        UTEST_FOREACH(count,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 64, 65, 100, 999, 0xfff)
        {
            for (size_t mask=0; mask <= 0x03; ++mask)
            {
                printf("Testing %s on input buffer of %d bytes, mask=0x%x...\n", label, int(count), int(mask));

                ByteBuffer a0(count, align, mask & 0x01);
                ByteBuffer b0(count, align, mask & 0x02);
                a0.randomize();
                b0.randomize();

                ByteBuffer a1(a0);
                ByteBuffer b1(b0);
                ByteBuffer a2(a0);
                ByteBuffer b2(b0);

                // Call functions
                generic::memswap(a1, b1, count);
                func(a2, b2, count);

                UTEST_ASSERT_MSG(a1.valid(), "Buffer a1 corrupted");
                UTEST_ASSERT_MSG(b1.valid(), "Buffer b1 corrupted");
                UTEST_ASSERT_MSG(a2.valid(), "Buffer a2 corrupted");
                UTEST_ASSERT_MSG(b2.valid(), "Buffer b2 corrupted");

                // Compare buffers
                if ((!a1.equals(a2)) || (!b1.equals(b2)))
                {
                    a0.dump("a0");
                    b0.dump("b0");
                    a1.dump("a1");
                    b1.dump("b1");
                    a2.dump("a2");
                    b2.dump("b2");

                    UTEST_FAIL_MSG("Output of functions for test '%s' differs", label);
                }
            }
        }
    }

    UTEST_MAIN
    {
        #define CALL(func, align) \
            call(#func, align, func)

        IF_ARCH_X86(CALL(x86::memswap, sizeof(umword_t)));
        IF_ARCH_X86(CALL(sse::memswap, 16));
        IF_ARCH_X86(CALL(avx::memswap, 32));
        IF_ARCH_X86(CALL(avx512::memswap, 64));

//        IF_ARCH_ARM(CALL(arm::memswap, sizeof(umword_t)));
//        IF_ARCH_ARM(CALL(neon_d32::memswap, 16));

//        IF_ARCH_AARCH64(CALL(aarch64::memswap, sizeof(umword_t)));
//        IF_ARCH_AARCH64(CALL(asimd::memswap, 16));
    }
UTEST_END



