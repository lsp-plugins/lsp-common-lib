/*
 * Copyright (C) 2024 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2024 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 30 авг. 2024 г.
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

#include <lsp-plug.in/stdlib/locale.h>
#include <lsp-plug.in/test-fw/utest.h>

using namespace lsp;

UTEST_BEGIN("common", locale)

    UTEST_MAIN
    {
        double value = 1234.5678;

        printf("Testing locale setup");
        {
            SET_LOCALE_SCOPED(LC_ALL, "C");
            printf("  Floating-point number using 'C' locale: %.4f\n", value);
        }

        printf("  Floating-point number using current locale: %.4f\n", value);
    }

UTEST_END





