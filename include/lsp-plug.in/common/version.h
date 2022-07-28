/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 3 мая 2020 г.
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

#ifndef LSP_PLUG_IN_COMMON_VERSION_H_
#define LSP_PLUG_IN_COMMON_VERSION_H_

//-----------------------------------------------------------------------------
// Version of headers
#define LSP_COMMON_LIB_MAJOR            1
#define LSP_COMMON_LIB_MINOR            0
#define LSP_COMMON_LIB_MICRO            21

#if defined(LSP_IDE_DEBUG)
    #define LSP_COMMON_LIB_EXPORT
    #define LSP_COMMON_LIB_CEXPORT
    #define LSP_COMMON_LIB_IMPORT
    #define LSP_COMMON_LIB_CIMPORT
#elif defined(LSP_COMMON_LIB_PUBLISHER)
    #define LSP_COMMON_LIB_EXPORT       LSP_SYMBOL_EXPORT
    #define LSP_COMMON_LIB_CEXPORT      LSP_CSYMBOL_EXPORT
    #define LSP_COMMON_LIB_IMPORT       LSP_SYMBOL_EXPORT
    #define LSP_COMMON_LIB_CIMPORT      LSP_CSYMBOL_EXPORT
#else
    #define LSP_COMMON_LIB_EXPORT
    #define LSP_COMMON_LIB_CEXPORT
    #define LSP_COMMON_LIB_IMPORT       LSP_SYMBOL_IMPORT
    #define LSP_COMMON_LIB_CIMPORT      LSP_CSYMBOL_IMPORT
#endif

#endif /* LSP_PLUG_IN_COMMON_VERSION_H_ */
