/*
 * Copyright (C) 2024 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2024 Vladimir Sadovnikov <sadko4u@gmail.com>
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

#ifndef LSP_PLUG_IN_COMMON_FINALLY_H_
#define LSP_PLUG_IN_COMMON_FINALLY_H_

#include <lsp-plug.in/common/version.h>
#include <lsp-plug.in/common/variadic.h>

namespace lsp
{
    template <class T>
    class FinallyExecutor
    {
        private:
            T       sActor;

        public:
            inline FinallyExecutor(T && actor): sActor(lsp::move(actor)) {}
            inline FinallyExecutor(T & actor) : sActor(actor) {}
            ~FinallyExecutor()  { sActor(); }
    };

    struct FinallyExecutorInit
    {
        template <class T>
        inline FinallyExecutor<T> operator + (T & actor)
        {
            return FinallyExecutor<T>(actor);
        }

        template <class T>
        inline FinallyExecutor<T> operator + (T && actor)
        {
            return FinallyExecutor<T>(lsp::move(actor));
        }
    };

    #define lsp_impl_finally2(id, prefix) prefix ## id ## __
    #define lsp_impl_finally1(id, prefix) lsp_impl_finally2(id, prefix)
    #define lsp_impl_finally0(id) \
        auto lsp_impl_finally1(id, lsp_finally_function) = ::lsp::FinallyExecutorInit{} + [&]() -> void

    #define lsp_finally lsp_impl_finally0(__COUNTER__)

} /* namespace lsp */

#endif /* LSP_PLUG_IN_COMMON_FINALLY_H_ */
