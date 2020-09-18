/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 30 июл. 2020 г.
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
#include <lsp-plug.in/test-fw/utest.h>

using namespace lsp;

UTEST_BEGIN("common", mword)

    void test_umword()
    {
        umword_t w1, w2;
        w1 = UMWORD_MAX;
        w2 = w1 + 1;
        UTEST_ASSERT(w2 == UMWORD_MIN);
        UTEST_ASSERT(w2 < w1);
    }

    void test_smword()
    {
        smword_t w1, w2;
        w1 = SMWORD_MAX;
        w2 = w1 + 1;
        UTEST_ASSERT(w2 == SMWORD_MIN);
        UTEST_ASSERT(w2 < w1);
    }

    UTEST_MAIN
    {
        test_umword();
        test_smword();
    }

UTEST_END


