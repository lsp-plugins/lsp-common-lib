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

#ifndef LSP_COMMON_LIB_INCLUDE_LSP_PLUG_IN_COMMON_SINGLETONE_H_
#define LSP_COMMON_LIB_INCLUDE_LSP_PLUG_IN_COMMON_SINGLETONE_H_

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

            volatile uatomic_t  state;

        public:
            explicit singletone_t() { state = ST_UNINITIALIZED; }
            ~ singletone_t() { }

        public:
            /** Check that singletone data the barrier is responsible for is initialized
             *
             * @return true if singletone is initialized
             */
            inline bool initialized() const { return state == ST_INITIALIZED; }

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


#endif /* LSP_COMMON_LIB_INCLUDE_LSP_PLUG_IN_COMMON_SINGLETONE_H_ */
