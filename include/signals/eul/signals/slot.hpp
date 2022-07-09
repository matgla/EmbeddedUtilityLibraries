// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>

#include "eul/utils/assert.hpp"
#include "eul/container/observable/observing_node.hpp"
#include "eul/functional/function.hpp"

namespace eul::signals 
{

template <class Functor, std::size_t Size>
class slot;

template <std::size_t Size, class ReturnType, class... Args>
class slot<ReturnType(Args...), Size>
{
public:
    using self_type = slot<ReturnType(Args...), Size>;
    using observed_type = eul::container::observing_node<self_type*>;
    using callback_type = eul::function<ReturnType(Args...), Size>;

    explicit slot(callback_type callback)
        : observing_node_(this)
        , callback_(std::move(callback))
    {
    }

    slot()
        : observing_node_(this)
    {
    }

    observed_type& observing_node()
    {
        return observing_node_;
    }

    void disconnect()
    {
        observing_node_.reset();
    }

    ReturnType operator()(Args... args) const
    {
        eul_assert_msg(callback_, "Slot is not initialized");
        return callback_(args...);
    }

    ReturnType operator()(Args... args)
    {
        eul_assert_msg(callback_, "Slot is not initialized");
        return callback_(args...);
    }

    template <typename CallbackType>
    auto& operator=(const CallbackType& callback)
    {
        callback_ = callback;
        return *this;
    }

    explicit operator bool() const noexcept
    {
        return callback_.operator bool();
    }
private:
    observed_type observing_node_;
    callback_type callback_;
};

} // namespace eul::signals
