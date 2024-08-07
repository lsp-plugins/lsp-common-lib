/*
 * Copyright (C) 2024 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2024 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 4 нояб. 2022 г.
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

#ifndef LSP_PLUG_IN_COMMON_SINGLETONE_H_
#define LSP_PLUG_IN_COMMON_SINGLETONE_H_

#include <lsp-plug.in/common/version.h>

#include <lsp-plug.in/common/atomic.h>

namespace lsp
{
    /**
     * Singletone barrier that holds information about the initialization of the singletone
     */
    struct LSP_COMMON_LIB_PUBLIC singletone_t
    {
        private:
            enum {
                ST_UNINITIALIZED,
                ST_INITIALIZING,
                ST_INITIALIZED
            };

            mutable uatomic_t       state;

        public:
            explicit singletone_t() { atomic_store(&state, ST_UNINITIALIZED); }
            ~ singletone_t() { }

        public:
            /** Check that singletone data the barrier is responsible for is not initialized
             *
             * @return true if singletone is initialized
             */
            inline bool uninitialized() const   { return atomic_load(&state) == ST_UNINITIALIZED; }


            /** Check that singletone data the barrier is responsible for is initialized
             *
             * @return true if singletone is initialized
             */
            inline bool initialized() const     { return atomic_load(&state) == ST_INITIALIZED; }

            /** Check that singletone data the barrier is responsible for is in initialization state
             *
             * @return true if singletone is initialized
             */
            inline bool initializing() const    { return atomic_load(&state) == ST_INITIALIZING; }

            /** Lock singletone barrier for initialization process
             *
             * @return true if the caller thread has acquired lock of the singletone for initialization
             */
            bool lock_for_initialization();

            /**
             * Mark singletone barrier as initialized
             * @return true if state has changed to initialized
             */
            bool mark_initialized();
    };

    typedef struct singletone_t singletone_t;

    struct SingletoneInitializer
    {
        private:
            singletone_t & singletone;

        public:
            explicit inline SingletoneInitializer(singletone_t & in_singletone): singletone(in_singletone)  {}

            template <class T>
                inline void operator + (T & actor)
                {
                    if (!singletone.lock_for_initialization())
                        return;
                    actor();
                    singletone.mark_initialized();
                }
            template <class T>
                inline void operator + (T && actor)
                {
                    if (!singletone.lock_for_initialization())
                        return;
                    actor();
                    singletone.mark_initialized();
                }
    };

    #define lsp_impl_singletone_init0(singletone, id) \
        SingletoneInitializer(singletone) + [&]() -> void

    #define lsp_singletone_init(singletone) lsp_impl_singletone_init0((singletone), __COUNTER__)

} /* namespace lsp */


#endif /* LSP_PLUG_IN_COMMON_SINGLETONE_H_ */
