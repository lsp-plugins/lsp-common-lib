/*
 * Copyright (C) 2026 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2026 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 21 нояб. 2020 г.
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

#ifndef LSP_PLUG_IN_STDLIB_STDLIB_H_
#define LSP_PLUG_IN_STDLIB_STDLIB_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>

#include <stdlib.h>


namespace lsp
{
    /**
     * Comparison function for sort
     * @param a first argument to compare
     * @param b second argument to compare
     * @param arg additional parameter passed to comparator
     * @return negative value if a < b, positive value if b > a, 0 if equal
     */
    typedef int (*sort_compar_t)(const void *a, const void *b, void *arg);

    /**
     * Pointer to the sort function
     * @param data data to sort
     * @param count number of elements
     * @param szof size of each element
     * @param compar comparison function
     * @param arg sort argument
     */
    typedef void (*sort_r_t)(void *data, size_t count, size_t szof, sort_compar_t compar, void *arg);

    /**
     * Perform quick sort of the data using the comparison function that accepts an argument
     *
     * @param data array to sort
     * @param count number of elements in array
     * @param szof size of each element
     * @param compar comparison function
     * @param arg argument passed to the comparison function
     */
    LSP_COMMON_LIB_PUBLIC
    void qsort_r(void *data, size_t count, size_t szof, sort_compar_t compar, void *arg);

    /**
     * Perform stable sort of the data using the comparison function that accepts an argument
     *
     * @param data array to sort
     * @param count number of elements in array
     * @param szof size of each element
     * @param compar comparison function
     * @param arg argument passed to the comparison function
     */
    LSP_COMMON_LIB_PUBLIC
    void ssort_r(void *data, size_t count, size_t szof, sort_compar_t compar, void *arg);
} /* namespace lsp */

#endif /* LSP_PLUG_IN_STDLIB_STDLIB_H_ */
