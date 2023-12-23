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

#include <utility>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node_const_iterator.hpp"
#include "eul/container/observable/observing_node_iterator.hpp"

namespace eul::container
{

template <typename T>
class observing_list;

template <typename T>
class observing_node
{
public:
    using iterator       = observing_node_iterator<T>;
    using const_iterator = observing_node_const_iterator<T>;
    using data_type      = T;
    template <typename... Args>
    explicit observing_node(Args... args);
    ~observing_node();

    observing_node(const observing_node<T>& node)               = delete;
    observing_node<T>& operator=(const observing_node<T>& node) = delete;

    observing_node(observing_node<T>&& node) noexcept;
    observing_node<T>& operator=(observing_node<T>&& node) noexcept = default;

    void reset();

    template <typename... Args>
    void reset(Args&&... args);

    [[nodiscard]] const observing_node<T>* next() const;
    observing_node<T>* next();
    [[nodiscard]] const observing_node<T>* prev() const;
    observing_node<T>* prev();

    void set_next(observing_node<T>* node);
    void set_prev(observing_node<T>* node);
    void set_prev(observing_list<observing_node<T>>* list);

    [[nodiscard]] bool is_subscribed() const;

    void reset_list();

    T& data();
    [[nodiscard]] const T& data() const;

    const T& operator*() const;
    const T* operator->() const noexcept;
    T& operator*();
    T* operator->() noexcept;

private:
    T data_;
    observing_node<T>* next_                 = nullptr;
    observing_node<T>* prev_                 = nullptr;
    observing_list<observing_node<T>>* list_ = nullptr;
};


template <typename T>
template <typename... Args>
observing_node<T>::observing_node(Args... args)
    : data_{args...}
{
}

template <typename T>
observing_node<T>::~observing_node()
{
    reset();
}

template <typename T>
observing_node<T>::observing_node(observing_node<T>&& node) noexcept
    : data_{node.data_}
    , next_{node.next_}
    , prev_{node.prev_}
    , list_{node.list_}
{
    // unregister old
    list_->swap(&node, this);
    node.reset();
}


template <typename T>
void observing_node<T>::reset()
{
    if (prev_)
    {
        prev_->set_next(next_);
    }
    if (next_)
    {
        next_->set_prev(prev_);
    }
    if (list_)
    {
        list_->set_root(next_);
        if (next_)
        {
            next_->set_prev(list_);
        }
    }
    prev_ = nullptr;
    next_ = nullptr;
    list_ = nullptr;
}

template <typename T>
template <typename... Args>
void observing_node<T>::reset(Args&&... args)
{
    data_ = T{args...};
}

template <typename T>
const observing_node<T>* observing_node<T>::next() const
{
    return next_;
}

template <typename T>
observing_node<T>* observing_node<T>::next()
{
    return next_;
}

template <typename T>
const observing_node<T>* observing_node<T>::prev() const
{
    return prev_;
}

template <typename T>
observing_node<T>* observing_node<T>::prev()
{
    return prev_;
}

template <typename T>
void observing_node<T>::set_next(observing_node<T>* node)
{
    next_ = node;
}

template <typename T>
void observing_node<T>::set_prev(observing_node<T>* node)
{
    prev_ = node;
}

template <typename T>
void observing_node<T>::set_prev(observing_list<observing_node<T>>* list)
{
    list_ = list;
}

template <typename T>
bool observing_node<T>::is_subscribed() const
{
    return prev_ != nullptr || next_ != nullptr || list_ != nullptr;
}

template <typename T>
void observing_node<T>::reset_list()
{
    list_ = nullptr;
}

template <typename T>
T& observing_node<T>::data()
{
    return data_;
}

template <typename T>
const T& observing_node<T>::data() const
{
    return data_;
}

template <typename T>
const T& observing_node<T>::operator*() const
{
    return data_;
}

template <typename T>
const T* observing_node<T>::operator->() const noexcept
{
    return &data_;
}

template <typename T>
T& observing_node<T>::operator*()
{
    return data_;
}

template <typename T>
T* observing_node<T>::operator->() noexcept
{
    return &data_;
}

} // namespace eul::container
