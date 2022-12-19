/*
 * Copyright (C) 2022 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2022 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins-sampler
 * Created on: 4 нояб. 2022 г.
 *
 * lsp-plugins-sampler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins-sampler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins-sampler. If not, see <https://www.gnu.org/licenses/>.
 */

#include <lsp-plug.in/common/singletone.h>
#include <lsp-plug.in/test-fw/utest.h>

UTEST_BEGIN("common", singletone)

    UTEST_MAIN
    {
        singletone_t singletone;

        printf("Testing singletone state transition...\n");
        UTEST_ASSERT( singletone.uninitialized() );

        lsp_singletone_init(singletone) {
            UTEST_ASSERT( singletone.initializing() );
        };
        UTEST_ASSERT( singletone.initialized() );

        lsp_singletone_init(singletone) {
            UTEST_FAIL_MSG( "This should not happen because singletone is already initialized" );
        };
        UTEST_ASSERT( singletone.initialized() );
    }
UTEST_END;



