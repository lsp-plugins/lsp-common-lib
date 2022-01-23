/*
 * Copyright (C) 2022 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2022 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 24 янв. 2022 г.
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
#include <lsp-plug.in/stdlib/stdlib.h>

namespace lsp
{
    int version_cmp(const version_t *a, const version_t *b)
    {
        int diff = a->major - b->major;
        if (diff != 0)
            return diff;
        diff = a->minor - b->minor;
        if (diff != 0)
            return diff;
        return a->micro - b->micro;
    }

    int version_cmp(const version_t &a, const version_t &b)
    {
        return version_cmp(&a, &b);
    }

    bool version_copy(version_t *dst, const version_t *src)
    {
        dst->major  = src->major;
        dst->minor  = src->minor;
        dst->micro  = src->micro;
        if (src->branch == NULL)
        {
            dst->branch = NULL;
            return true;
        }

        dst->branch = strdup(src->branch);
        return dst->branch != NULL;
    }

    void version_destroy(version_t *version)
    {
        if (version->branch != NULL)
        {
            free(const_cast<char *>(version->branch));
            version->branch = NULL;
        }
        version->major  = 0;
        version->minor  = 0;
        version->micro  = 0;
    }
} // namespace lsp





