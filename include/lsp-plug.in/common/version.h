/*
 * version.h
 *
 *  Created on: 3 мая 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_VERSION_H_
#define LSP_PLUG_IN_COMMON_VERSION_H_

//-----------------------------------------------------------------------------
// Version of headers
#define LSP_COMMON_LIB_MAJOR            1
#define LSP_COMMON_LIB_MINOR            0
#define LSP_COMMON_LIB_MICRO            8

#ifdef LSP_COMMON_LIB_BUILTIN
    #define LSP_COMMON_LIB_EXPORT
    #define LSP_COMMON_LIB_CEXPORT
    #define LSP_COMMON_LIB_IMPORT       LSP_SYMBOL_IMPORT
    #define LSP_COMMON_LIB_CIMPORT      LSP_CSYMBOL_IMPORT
#else
    #define LSP_COMMON_LIB_EXPORT       LSP_SYMBOL_EXPORT
    #define LSP_COMMON_LIB_CEXPORT      LSP_CSYMBOL_EXPORT
    #define LSP_COMMON_LIB_IMPORT       LSP_SYMBOL_IMPORT
    #define LSP_COMMON_LIB_CIMPORT      LSP_CSYMBOL_IMPORT
#endif

#endif /* LSP_PLUG_IN_COMMON_VERSION_H_ */
