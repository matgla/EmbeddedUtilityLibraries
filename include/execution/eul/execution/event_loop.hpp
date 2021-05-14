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

#include <tuple>

#include "eul/function.hpp"


namespace eul
{
namespace detail
{
template <std::size_t, typename T>
struct convert;

template <std::size_t CallbackSize, typename T>
struct convert
{
    using callback_type = function<void(const T&), CallbackSize>;
};

template <std::size_t, typename... Args>
struct binder;

template <std::size_t CallbackSize, typename... Args>
struct binder<CallbackSize, std::tuple<Args...>>
{
    typedef std::tuple<typename convert<CallbackSize, Args>::callback_type...> type;
};
} // namespace detail

template <typename Event>
class event_loop;

template <std::size_t CallbackSize, typename... Events>
struct events
{
    constexpr static std::size_t callbackSize = CallbackSize;
    using event_list                          = std::tuple<Events...>;
};

template <typename Events>
class event_loop
{
public:
    template <typename EventType>
    using callback_type = function<void(const EventType&), Events::callbackSize>;

    template <typename EventType>
    void register_event(const callback_type<EventType>& callback)
    {
        std::get<callback_type<EventType>>(callbacks_) = callback;
    }

    template <typename EventType>
    constexpr void dispatch(const EventType& event)
    {
        if (!std::get<callback_type<EventType>>(callbacks_))
        {
            return;
        }
        std::get<callback_type<EventType>>(callbacks_)(event);
    }

    template <typename EventType>
    constexpr void unregister()
    {
        std::get<callback_type<EventType>>(callbacks_) = nullptr;
    }

private:
    typename detail::binder<Events::callbackSize, typename Events::event_list>::type callbacks_;
};

} // namespace eul
