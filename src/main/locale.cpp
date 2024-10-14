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

#ifndef PLATFORM_WINDOWS

namespace lsp
{
    namespace detail
    {
        LSP_COMMON_LIB_PUBLIC
        locale_t create_locale(int type, const char *name)
        {
            int flags;
            switch (type)
            {
                case LC_CTYPE:          flags   = LC_CTYPE_MASK; break;
                case LC_NUMERIC:        flags   = LC_NUMERIC_MASK; break;
                case LC_TIME:           flags   = LC_TIME_MASK; break;
                case LC_COLLATE:        flags   = LC_COLLATE_MASK; break;
                case LC_MONETARY:       flags   = LC_MONETARY_MASK; break;
                case LC_MESSAGES:       flags   = LC_MESSAGES_MASK; break;
                case LC_ALL:            flags   = LC_ALL_MASK; break;
        #if defined(LC_PAPER)
                case LC_PAPER:          flags   = LC_PAPER_MASK; break;
        #endif
        #if defined(LC_NAME)
                case LC_NAME:           flags   = LC_NAME_MASK; break;
        #endif
        #if defined(LC_ADDRESS)
                case LC_ADDRESS:        flags   = LC_ADDRESS_MASK; break;
        #endif
        #if defined(LC_TELEPHONE)
                case LC_TELEPHONE:      flags   = LC_TELEPHONE_MASK; break;
        #endif
        #if defined(LC_MEASUREMENT)
                case LC_MEASUREMENT:    flags   = LC_MEASUREMENT_MASK; break;
        #endif
        #if defined(LC_IDENTIFICATION)
                case LC_IDENTIFICATION: flags   = LC_IDENTIFICATION_MASK; break;
        #endif

                default:
                    return INVALID_LOCALE;
            }

            return newlocale(flags, name, INVALID_LOCALE);
        }

    } /* namespace detail */
} /* namespace lsp */

#endif /* PLATFORM_WINDOWS */
