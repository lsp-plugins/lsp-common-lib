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

#include <lsp-plug.in/common/singletone.h>

namespace lsp
{
    bool singletone_t::lock_for_initialization()
    {
        // Synchronization barrier: ensure that DSP library is already initialized
        while (true)
        {
            uatomic_t current_state = state;
            switch (current_state)
            {
                case ST_UNINITIALIZED:
                    // Try to obtain the lock
                    if (atomic_cas(&state, current_state, ST_INITIALIZING))
                        return true; // We have obtained the lock
                    break;
                case ST_INITIALIZED:
                    return false;
                case ST_INITIALIZING: // Another thread is initializing the library
                default:
                    // Wait until state has changed
                    break;
            }
        }
    }

    bool singletone_t::mark_initialized()
    {
        while (true)
        {
            uatomic_t current_state = state;
            if (current_state != ST_INITIALIZING)
                return false;
            if (atomic_cas(&state, current_state, ST_INITIALIZED))
                return true;
        }
    }

} /* namespace lsp */

