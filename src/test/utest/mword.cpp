/*
 * mword.cpp
 *
 *  Created on: 30 июл. 2020 г.
 *      Author: sadko
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


