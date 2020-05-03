/*
 * alloc.h
 *
 *  Created on: 3 апр. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_ALLOC_H_
#define LSP_PLUG_IN_COMMON_ALLOC_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/types.h>
#include <stdlib.h>

namespace lsp
{
    inline size_t align_size(size_t size, size_t align)
    {
        size_t off = size % align;
        return (off) ? (size + align - off) : size;
    }

    template <class T>
        inline T *align_ptr(T *src, size_t align = DEFAULT_ALIGN)
        {
            uintptr_t x     = uintptr_t(src);
            uintptr_t off   = x % align;
            return (off) ?
                reinterpret_cast<T *>(x + align - off) :
                src;
        }

    template <class T>
        inline bool is_ptr_aligned(T *src, size_t align = DEFAULT_ALIGN)
        {
            ptrdiff_t x     = ptrdiff_t(src);
            return !(x % align);
        }

    /** Allocate aligned pointer
     *
     * @param ptr reference to pointer to store allocated pointer for future free() operation
     * @param count number of elements to allocate
     * @param align alignment, should be power of 2, by default DEFAULT_ALIGN
     * @return aligned pointer as a result of alignment of ptr to align boundary or NULL if allocation failed
     * @example
     *      void *x = NULL;
     *      float *a = alloc_aligned<float>(x, 1000); // Allocate 1000 floats aligned to DEFAULT_ALIGN boundary
     *      if (a == NULL)
     *          return ERROR;
     *      // Do some stuff
     *      free_aligned(x);
     *      a = NULL;
     */
    template <class T, class P>
        inline T *alloc_aligned(P * &ptr, size_t count, size_t align=DEFAULT_ALIGN)
        {
            // Check for power of 2
            if ((!align) || (align & (align-1)))
                return NULL;

            // Allocate data
            void *p         = ::malloc((count * sizeof(T)) + align);
            if (p == NULL)
                return NULL;

            // Store pointer
            ptr             = reinterpret_cast<P *>(p);

            // Return aligned pointer
            ptrdiff_t x     = ptrdiff_t(p);
            ptrdiff_t mask  = align-1;
            return reinterpret_cast<T *>((x & mask) ? ((x + align)&(~mask)) : x);
        }

    /** Free aligned pointer and write NULL to it
     *
     * @param ptr pointer to free
     */
    template <class P>
        inline void free_aligned(P * &ptr)
        {
            if (ptr == NULL)
                return;
            P *tptr = ptr;
            ptr = NULL;
            ::free(tptr);
        }
}

#endif /* LSP_PLUG_IN_COMMON_ALLOC_H_ */
