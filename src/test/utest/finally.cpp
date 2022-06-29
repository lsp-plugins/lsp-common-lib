/*
 * Copyright (C) 2022 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2022 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 29 июн. 2022 г.
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

using namespace lsp;

UTEST_BEGIN("common", finally)

    void test_finally()
    {
        char buf[80], tmp[8];
        buf[0] = '\0';

        {
            strcat(buf, "A1");
            lsp_finally (
                strcat(buf, "F1");
            );
            strcat(buf, "B1");

            {
                strcat(buf, "A2");
                lsp_finally (
                    strcat(buf, "F2");
                );
                strcat(buf, "B2");

                for (size_t i=0; i<4; ++i)
                {
                    snprintf(tmp, sizeof(tmp), "X%d", int(i));
                    strcat(buf, tmp);
                    lsp_finally (
                        snprintf(tmp, sizeof(tmp), "W%d", int(i));
                        strcat(buf, tmp);
                    );
                    snprintf(tmp, sizeof(tmp), "Y%d", int(i));
                    strcat(buf, tmp);
                } // for
                strcat(buf, "C2");
            } // block 1

            strcat(buf, "C1");
        } // block 2

        UTEST_ASSERT(strcmp(buf, "A1B1A2B2X0Y0W0X1Y1W1X2Y2W2X3Y3W3C2F2C1F1") == 0);
    }


    UTEST_MAIN
    {
        test_finally();
    }
UTEST_END;



